// IGR1S


#include "AbilitySyste/Abilities/AuraDamageAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle= MakeOutgoingGameplayEffectSpec(DamageEffectClass,1.0f);
	const float ScaleDamage=Damage.GetValueAtLevel(GetAbilityLevel());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle,DamageType,ScaleDamage);
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	
}

FDamageEffectParams UAuraDamageAbility::MakeDamageEffectParams(AActor* TargetActor)const
{
	FDamageEffectParams Params;
	Params.WorldContextObject=GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass=DamageEffectClass;
	Params.SourceASC=GetAbilitySystemComponentFromActorInfo();
	Params.TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.BaseDamage=Damage.GetValueAtLevel(GetAbilityLevel());
	Params.AbilityLevel=GetAbilityLevel();
	Params.DamageType=DamageType;
	Params.DebuffChance=DebuffChance;
	Params.DebuffDamage=DebuffDamage;
	Params.DebuffDuration=DebuffDuration;
	Params.DebuffFrequency=DebuffFrequency;
	Params.DeathImpulseMagnitude=DeathImpulseMagnitude;
	Params.KnockbackForceMagnitude=KnockbackForceMagnitude;
	Params.KnocKbackChance=KnockbackChance;
	if (IsValid(TargetActor))
	{
		FRotator Rotation=(TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()).Rotation();
		Rotation.Pitch=45.f;
		const FVector ToTarget=Rotation.Vector();
		Params.DeathImpulse=ToTarget*DeathImpulseMagnitude;
		Params.KnockbackForce=ToTarget*KnockbackForceMagnitude;
	}
	return Params;
}

float UAuraDamageAbility::GetDamageAtLevel()const
{
	return Damage.GetValueAtLevel(GetAbilityLevel());
}

FTaggedMontage UAuraDamageAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const 
{
	if (TaggedMontages.Num() > 0)
	{
		const int32 Selection =  FMath::RandRange(0,TaggedMontages.Num()-1);
		return TaggedMontages[Selection];
	}
	return FTaggedMontage();
}


