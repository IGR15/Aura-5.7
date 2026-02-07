// IGR1S


#include "AbilitySyste/MMC/MMC_MaxMana.h"
#include "AbilitySyste/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/ModifierDependencyInterface.h"


UMMC_MaxMana::UMMC_MaxMana()
{
	InelligenceDef.AttributeToCapture=UAuraAttributeSet::GetIntelligenceAttribute();
	InelligenceDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	InelligenceDef.bSnapshot=false;

	RelevantAttributesToCapture.Add(InelligenceDef);
}
float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target optional
	const FGameplayTagContainer* SourceTag= Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag= Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTag;
	EvaluateParameters.TargetTags=TargetTag;
	float Inelligenc=0.0f;
	GetCapturedAttributeMagnitude(InelligenceDef,Spec,EvaluateParameters,Inelligenc);
	Inelligenc=FMath::Max<float>(Inelligenc,0.0f);
	//we can cast source object into an interface that way we can get the player level
	int32 PlayerLevel=1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel=ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}
	return 30.f+2.5f*Inelligenc+5.f*PlayerLevel;
}

FOnExternalGameplayModifierDependencyChange* UMMC_MaxMana::GetExternalModifierDependencyMulticast(
	const FGameplayEffectSpec& Spec, UWorld* World) const
{
	AActor* Instigator=Spec.GetContext().GetInstigator();
	IModifierDependencyInterface* MDI=Cast<IModifierDependencyInterface>(Instigator);
	if (MDI)
	{
		return MDI->GetOnModifierDependencyChanged();
	}
	return Super::GetExternalModifierDependencyMulticast(Spec, World);
}

