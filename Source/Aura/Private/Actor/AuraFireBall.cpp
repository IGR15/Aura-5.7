// IGR1S


#include "Actor/AuraFireBall.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayCueManager.h"
#include "AbilitySyste/AuraAbilitySystemLibrary.h"
#include "Components/AudioComponent.h"


void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	StartOutGoingTimeline();
}

void AAuraFireBall::OnHit()
{
	if (GetOwner())
	{
		FGameplayCueParameters CueParameters;
		CueParameters.Location=GetActorLocation();
		
		UGameplayCueManager::ExecuteGameplayCue_NonReplicated(GetOwner(),FAuraGameplayTags::Get().GameplayCue_FireBlast,CueParameters);
	}
	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	bHit=true;
}

void AAuraFireBall::OnsphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverLap(OtherActor))return;
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			const FVector DeathImpulse=GetActorForwardVector()*DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse=DeathImpulse;
			
			DamageEffectParams.TargetASC=TargetASC;
			UAuraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}
		
		
	}

}

