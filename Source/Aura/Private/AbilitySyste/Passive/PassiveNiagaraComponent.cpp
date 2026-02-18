// IGR1S


#include "AbilitySyste/Passive/PassiveNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySyste/AuraAbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"


// Sets default values for this component's properties
UPassiveNiagaraComponent::UPassiveNiagaraComponent()
{
	
	bAutoActivate = false;

	
}

void UPassiveNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UAuraAbilitySystemComponent* AuraASC=Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()));
	if (AuraASC && !AuraASC->ActivatePassiveEffectDelegate.IsBoundToObject(this))
	{
		AuraASC->ActivatePassiveEffectDelegate.AddUObject(this,&UPassiveNiagaraComponent::OnPassiveActivate);
	}
	else if (ICombatInterface* CombatInterface=Cast<ICombatInterface>(GetOwner()))
	{
		CombatInterface->GetOnASCRegisteredDelegate().AddLambda([this](UAbilitySystemComponent* ASC)
		{
			UAuraAbilitySystemComponent* AuraASC=Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()));
			if (AuraASC && !AuraASC->ActivatePassiveEffectDelegate.IsBoundToObject(this))
			{
				AuraASC->ActivatePassiveEffectDelegate.AddUObject(this,&UPassiveNiagaraComponent::OnPassiveActivate);
			}
		});
	}
	
	
}

void UPassiveNiagaraComponent::OnPassiveActivate(const FGameplayTag& AbilityTag, bool bActivate)
{
	if (AbilityTag.MatchesTagExact(PassiveSpellTag))
	{
		if (bActivate && !IsActive())
		{
			Activate();
		}
		else
		{
			Deactivate();
		}
	}
}


