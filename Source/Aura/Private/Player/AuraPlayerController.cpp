// IGR1S


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySyste/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	Spline=CreateDefaultSubobject<USplineComponent>("Spline");
}
void AAuraPlayerController::AutoRun()
{
	if (APawn* ControlledPawn=GetPawn())
	{
		if (!bAutoRunning)return;
		//the location on the spline that is closest to the spline 
		const FVector LocationOnSpline=Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation()
			,ESplineCoordinateSpace::World);
		const FVector Direction=Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,
			ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination=(LocationOnSpline-CashedDestination).Length();
		if (DistanceToDestination<=AutoRunAcceptanceRadius)
		{
			bAutoRunning=false;
		}
	}
}
void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CurserTrace();
	AutoRun();
}

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount,ACharacter* TargetCaracter,bool bBlockedHit,bool bCriticalHit)
{
	if (IsValid(TargetCaracter)&& DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText= NewObject<UDamageTextComponent>(TargetCaracter,DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCaracter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount,bBlockedHit,bCriticalHit);
		
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))return;

	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting=ThisActor ? true : false;
		bAutoRunning=false;
	}
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}
void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputReleased))return;
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	if (!bTargeting&& !bShiftKeyDown )
	{

		const APawn* controlledPawn=GetPawn();
		if (FollowTime<= ShortPressThreshold&&controlledPawn)
		{
			if (UNavigationPath*NavPath =UNavigationSystemV1::FindPathToLocationSynchronously(this,
				controlledPawn->GetActorLocation(),CashedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLec:NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLec,ESplineCoordinateSpace::World);
				}
				if (NavPath->PathPoints.Num()>0)
				{
					CashedDestination=NavPath->PathPoints[NavPath->PathPoints.Num()-1];
					bAutoRunning=true;
					if(GetASC()&&!GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ClickNiagaraSystem,CashedDestination);

					}
				}
			}
		}
		FollowTime=0.f;
		bTargeting=false;
	}
	
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputHeld))return;
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	if (bTargeting||bShiftKeyDown)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime+=GetWorld()->GetDeltaSeconds();
		if (CurserHit.bBlockingHit) CashedDestination=CurserHit.ImpactPoint;
		if (APawn* ControlledPawn=GetPawn())
		{
			const FVector WorldDirection=(CashedDestination-ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent==nullptr)
	{
		AuraAbilitySystemComponent= Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}
	bShowMouseCursor = true;
	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;

	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
		
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this , &AAuraPlayerController::Move);

	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Started,this , &AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Completed,this , &AAuraPlayerController::ShiftReleased);

	AuraInputComponent->BindAbilityActions(InputConfig,this,
		&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))return;
	// Get 2D input vector from the input action (X = Right/Left, Y = Forward/Backward)
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// Get the controller's current rotation (camera view direction)
	const FRotator Rotation= GetControlRotation();
	// Create a yaw-only rotator (ignore pitch and roll to keep movement horizontal)
	const FRotator YawRotator(0.f,Rotation.Yaw,0.f);
	
	// Get forward vector (X axis) from yaw-only rotation for forward/back movement
	const FVector ForwardDirection= FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	// Get the right vector (Y axis) from full rotation for strafing movement
	const FVector RightDirection= FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	// Move the pawn if it exists
	if (APawn* ControlledPawn {GetPawn<APawn>()})
	{
		// Apply movement in the forward direction scaled by Y input
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		// Apply movement in the right direction scaled by X input
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
	// Processes movement input by converting 2D input into world-space directions.
	// Extracts forward and right vectors based on controller yaw and applies movement to the controlled pawn.

}
void AAuraPlayerController::CurserTrace()
{
	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_CursorTrace))
	{
		if (LastActor) LastActor->UnHighLightAcotr();
		if (ThisActor) ThisActor->UnHighLightAcotr();
		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}
	
	GetHitResultUnderCursor(ECC_Visibility,false,CurserHit);
	if (!CurserHit.bBlockingHit) return;
	LastActor=ThisActor;
	ThisActor=CurserHit.GetActor();
	//ThisActor=Cast<IEnemyInterface>(CurserHit.GetActor());
	if (LastActor!=ThisActor)
	{
		if (LastActor) LastActor->UnHighLightAcotr();
		if (ThisActor) ThisActor->HighLightActor();
	}
	/**
	 * Line trace from cursor. There are several scenarios:
	 * A. LastActor is null && ThisActor is null
	 *    - Do nothing
	 *
	 * B. LastActor is null && ThisActor is valid
	 *    - Highlight ThisActor
	 *
	 * C. LastActor is valid && ThisActor is null
	 *    - UnHighlight LastActor
	 *
	 * D. Both actors are valid, but LastActor != ThisActor
	 *    - UnHighlight LastActor, and Highlight ThisActor
	 *
	 * E. Both actors are valid, and are the same actor
	 *    - Do nothing
	 */
	// if (LastActor==nullptr)
	// {
	// 	if (ThisActor!=nullptr)
	// 	{
	// 		//case B
	// 		ThisActor->HighLightActor();
	// 	}else
	// 	{
	// 		//case B the else is not necessary 
	// 		
	// 	}
	// }
	// else //last Actor is vaild
	// {
	// 	if (ThisActor==nullptr)
	// 	{
	// 		//case C
	// 		LastActor->UnHighLightAcotr();
	// 	}
	// 	else //both are vaild
	// 	{
	// 		if (LastActor!=ThisActor)
	// 		{
	// 			//case D
	// 			LastActor->HighLightActor();
	// 			ThisActor->HighLightActor();
	// 		}
	// 		else //else is not necessary 
	// 		{
	// 			//case E
	// 		}
	// 	}
	// }

}


