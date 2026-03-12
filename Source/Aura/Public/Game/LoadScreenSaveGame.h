// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

class UGameplayAbility;
/**
 * 
 */
UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};

USTRUCT(BlueprintType)
struct FSavedAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,category="ClassDefaults")
	TSubclassOf<UGameplayAbility> GameplayAbility;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,category="ClassDefaults")
	FGameplayTag AbilityTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,category="ClassDefaults")
	FGameplayTag AbilityStatus = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,category="ClassDefaults")
	FGameplayTag AbilitySlot = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,category="ClassDefaults")
	FGameplayTag AbilityType = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,category="ClassDefaults")
	float AbilityLevel = 1.f;
	
};
inline bool operator==(const FSavedAbility& Left, const FSavedAbility& Right)
{
	return Left.AbilityTag == Right.AbilityTag;
}
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY()
	FString SlotName = FString();
	
	UPROPERTY()
	int32 SlotIndex = 0;
	
	UPROPERTY()
	FString PlayerName = FString("Default Name");
	
	UPROPERTY()
	FString MapName = FString("Default Map Name");

	UPROPERTY()
	FName PlayerStartTag;
	
	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SlotStatus = ESaveSlotStatus::Vacant;
	
	UPROPERTY()
	bool bFirstTimeLoadIn = true;
	
	/*
	 * Player 
	 */
	UPROPERTY()
	int32 PlayerLevel = 1;
	
	UPROPERTY()
	int32 PlayerXP = 0;
	
	UPROPERTY()
	int32 SpellPoints = 0;
	
	UPROPERTY()
	int32 AttributePoints = 0;
	
	/*Attributes*/
	UPROPERTY()
	float Strength = 0.f;
	
	UPROPERTY()
	float Intelligence = 0.f;
	
	
	UPROPERTY()
	float Resilience = 0.f;
	
	UPROPERTY()
	float Vigor = 0.f;
	
	/* Abilities*/
	
	UPROPERTY()
	TArray<FSavedAbility> SavedAbilities;
	
};
