// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "PassiveNiagaraComponent.generated.h"


class UAuraAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UPassiveNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPassiveNiagaraComponent();
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PassiveSpellTag;
	
protected:
	virtual void BeginPlay() override;
	
	void OnPassiveActivate(const FGameplayTag& AbilityTag,bool bActivate);
	
	void ActivateIfEquipped(UAuraAbilitySystemComponent* AuraASC);

};


