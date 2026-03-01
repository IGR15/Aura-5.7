// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayTagContainer.h"
#include "AuraGameModeBase.generated.h"
class USaveGame;
class UMVVM_LoadSlot;
class UAbilityInfo;
class UCharacterClassInfo;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo>CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly,Category="Ability Info")
	TObjectPtr<UAbilityInfo>AbilityInfo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Debuff Data")
	TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> DebuffTagToEffectMap;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame>LoadScreenSaveGameClass;
	
	void SaveSlotData(UMVVM_LoadSlot* LoadSlot,int32 SlotIndex);
	
};
