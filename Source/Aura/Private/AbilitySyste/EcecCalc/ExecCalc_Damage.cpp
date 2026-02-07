// IGR1S


#include "AbilitySyste/EcecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySyste/AuraAbilitySystemLibrary.h"
#include "AbilitySyste/AuraAttributeSet.h"
#include "AbilitySyste/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

//Raw Struct To capture attributes
struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,FireResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,LightningResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArcaneResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,PhysicalResistance,Target,false);
		/*
		 * here we are mapping / associating the game play tags with its capture definition 
		 */
		
		
	}
};
static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}
UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec, FAggregatorEvaluateParameters EvaluateParams, const TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const
{
	const FAuraGameplayTags& GameplayTags=FAuraGameplayTags::Get();
	for (TTuple<FGameplayTag,FGameplayTag>Pair: GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType=Pair.Key;
		const FGameplayTag& DebuffType=Pair.Value;
		const float TypeDamage= Spec.GetSetByCallerMagnitude(DamageType,false,-1.f);
		if (TypeDamage>-0.5f)//0.5 padding for floating point 
		{
			//detrmine if there was a successful Debuff
			const float SourceDebuffChance=Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance,false,-1.f);
			float TargetDebuffResistance=0.f;
			const FGameplayTag& ResistanceTag=GameplayTags.DamageTypesToResistance[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag],EvaluateParams,TargetDebuffResistance);
			TargetDebuffResistance=FMath::Max<float>(TargetDebuffResistance,0.f);
			const float EffectiveDebuffChance=SourceDebuffChance*(100-TargetDebuffResistance)/100.f;
			const bool bDebuff = FMath::RandRange(1,100)<EffectiveDebuffChance;
			if (bDebuff)
			{
				FGameplayEffectContextHandle ContextHandle= Spec.GetContext();

				UAuraAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle,true);
				UAuraAbilitySystemLibrary::SetDamageType(ContextHandle,DamageType);

				const float DebuffDamage=Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage,false,-1.f);
				const float DebuffDuration=Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration,false,-1.f);
				const float DebuffFrequency=Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency,false,-1.f);

				UAuraAbilitySystemLibrary::SetDebuffDamage(ContextHandle,DebuffDamage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(ContextHandle,DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle,DebuffFrequency);
			}
		}
	}
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition>TagsToCaptureDefs;

	const FAuraGameplayTags& Tags=FAuraGameplayTags::Get();
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor,DamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance,DamageStatics().BlockChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration,DamageStatics().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance,DamageStatics().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance,DamageStatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage,DamageStatics().CriticalHitDamageDef);
		
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire,DamageStatics().FireResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning,DamageStatics().LightningResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane,DamageStatics().ArcaneResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical,DamageStatics().PhysicalResistanceDef);
	
	const UAbilitySystemComponent* SourceASC=ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC=ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar=SourceASC? SourceASC->GetAvatarActor():nullptr;	
	AActor* TargetAvatar=TargetASC? TargetASC->GetAvatarActor():nullptr;

	int32 SourcePlayerLevel=1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel=ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel=1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel=ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	

	const FGameplayEffectSpec& Spec=ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTages=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags=SourceTages;
	EvaluateParams.TargetTags=TargetTags;

	//Debuff
	DetermineDebuff(ExecutionParams, Spec, EvaluateParams,TagsToCaptureDefs);
	
	//get Damage set by caller magnitude
	float Damage=0.f;
	/*
	 * and now here we know which damage type is associated with its resistance type thanks to the TMap TagsToCaptureDefs
	 */
	for (const auto& Pair:FAuraGameplayTags::Get().DamageTypesToResistance)
	{
		
		const FGameplayTag DamageTypeTag=Pair.Key;
		const FGameplayTag DamageResistanceTag=Pair.Value;
		checkf(TagsToCaptureDefs.Contains(DamageResistanceTag),TEXT("TagsToCaptureDefs doesn't contain tag: %s in ExecCalc_Damage "),*DamageResistanceTag.ToString());
		
		const FGameplayEffectAttributeCaptureDefinition CaptureDefinition = TagsToCaptureDefs[DamageResistanceTag];
		float DamageTypeValue=Spec.GetSetByCallerMagnitude(Pair.Key,false);
		float Resistance=0.f;

		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDefinition,EvaluateParams,Resistance);
		Resistance=FMath::Clamp(Resistance,0.f,100.f);

		DamageTypeValue+=(100.f-Resistance)/100.f;
		
		Damage+=DamageTypeValue;
	}
	
	//Capture BlockChance on Target, and determine if there was a successful Block
	float TargetBlockChance=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParams,TargetBlockChance);
	TargetBlockChance=FMath::Max<float>(TargetBlockChance,0.f);

	const bool bBlocked=FMath::RandRange(1,100)<TargetBlockChance;

	FGameplayEffectContextHandle ContextHandle=Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsBlockedHit(ContextHandle,bBlocked);
	
	// if block, halve the damage
	Damage=bBlocked ? Damage / 2.f : Damage;
	
	//ArmorPenetration Ignores a percentage of the target's armor 
	float TargetArmor=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParams,TargetArmor);
	TargetArmor=FMath::Max<float>(TargetArmor,0.f);

	float SourceArmorPenetration=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluateParams,SourceArmorPenetration);
	SourceArmorPenetration=FMath::Max<float>(SourceArmorPenetration,0.f);

	
	const UCharacterClassInfo* CharacterClassInfo=UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve= CharacterClassInfo->DamagecalculationCoeffficient->FindCurve(FName("ArmorPenetration"),FString());
	const float ArmorPenetrationCoefficient= ArmorPenetrationCurve->Eval(SourcePlayerLevel);
	
	//Armor Ignores a percentage of incoming Damage.
	const float EffectiveArmor=TargetArmor *(100-SourceArmorPenetration*ArmorPenetrationCoefficient)/100.f;
	const FRealCurve*EffectiveArmorCoefficientCurve=CharacterClassInfo->DamagecalculationCoeffficient->FindCurve(FName("EffectiveArmor"),FString());
	const float EffectiveArmorCoefficient=EffectiveArmorCoefficientCurve->Eval(TargetPlayerLevel);
	
	Damage*=(100-EffectiveArmor*EffectiveArmorCoefficient)/100.f;

	float SourceCriticalHitChance=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,EvaluateParams,SourceCriticalHitChance);
	SourceCriticalHitChance=FMath::Max<float>(SourceCriticalHitChance,0.f);

	float TargetCriticalHitResistance=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,EvaluateParams,TargetCriticalHitResistance);
	TargetCriticalHitResistance=FMath::Max<float>(TargetCriticalHitResistance,0.f);

	float SourceCriticalHitDamage=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,EvaluateParams,SourceCriticalHitDamage);
	SourceCriticalHitDamage=FMath::Max<float>(SourceCriticalHitDamage,0.f);

	const FRealCurve*EffectiveCriticalHitResistanceCurve=CharacterClassInfo->DamagecalculationCoeffficient->FindCurve(FName("CriticalHitResistance"),FString());
	const float EffectiveCriticalHitResistanceCoefficient=EffectiveCriticalHitResistanceCurve->Eval(TargetPlayerLevel);

	//Critical Hit Resistance reduces critical hit chance by a certain percentage 
	const float EffectiveSourceCriticalHitChance=SourceCriticalHitChance-TargetCriticalHitResistance*EffectiveCriticalHitResistanceCoefficient;
	const bool bCriticalHit=FMath::RandRange(1,100)< EffectiveSourceCriticalHitChance;
	
	UAuraAbilitySystemLibrary::SetIsCriticalHit(ContextHandle,bCriticalHit);
	
	Damage=bCriticalHit ? 2.f*Damage+SourceCriticalHitDamage : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
