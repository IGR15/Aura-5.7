// IGR1S


#include "Characters/AuraCharacter.h"
#include "NiagaraComponent.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySyste/AuraAbilitySystemComponent.h"
#include "AbilitySyste/Data/LevelUpInfo.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->bDoCollisionTest=false;

	CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation=false;
	
	LevelUpNiagaraComponent=CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate=false;
	
	UCharacterMovementComponent* CharacterMovementComponent=GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate = FRotator(0.f, 400.f, 0.f);

	CharacterMovementComponent->bConstrainToPlane = true;
	CharacterMovementComponent->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	CharacterClass=ECharacterClass::Mage;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//init ability actor info for the server
	InitAbilityActorInfor();
	AddCharacterAbilities();	
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//init ability actor info for the clint
	InitAbilityActorInfor();

}

void AAuraCharacter::AddToXP_Implementation(int32 InXP)
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToXP(InXP);
}

void AAuraCharacter::LevelUp_Implementation()
{
	MultiCastLevelUpParticles();
}
void AAuraCharacter::MultiCastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation=CameraComponent->GetComponentLocation();
		const FVector NiagaraLocation=LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation=(CameraLocation-NiagaraLocation).Rotation();

		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 AAuraCharacter::GetXP_Implementation() const
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetXP();
}

int32 AAuraCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AAuraCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->LevelUpInfo[Level].AttributePointAward;
}

int32 AAuraCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->LevelUpInfo[Level].SpellPointAward;
}



void AAuraCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToLevel(InPlayerLevel);

	if (UAuraAbilitySystemComponent* AuraASC=Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		AuraASC->UpdateAbilityStatuses(AuraPlayerState->GetPlayerLevel());
	}
}
void AAuraCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToAttributePoints(InAttributePoints);
}
void AAuraCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToSpellPoints(InSpellPoints);
}

int32 AAuraCharacter::GetAttributePoints_Implementation() const
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetAttributePoints();
}

int32 AAuraCharacter::GetSpellPoints_Implementation() const
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetSpellPoints();
}

int32 AAuraCharacter::GetPlayerLevel_Implementation()
{
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
	
}
void AAuraCharacter::InitAbilityActorInfor()
{
	
	AAuraPlayerState* AuraPlayerState= GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInofSet();
	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	AttributeSet=AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Debuff_Stun,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&AAuraCharacter::StunTagChanged);

	if (AAuraPlayerController* AuraPlayerController= Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD= Cast<AAuraHUD>( AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	
	}
	InitializeDefaultAttributes();
}


