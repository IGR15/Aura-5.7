// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass:uint8
{
	Mage,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TSubclassOf<UGameplayEffect>PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	FScalableFloat XPReward=FScalableFloat();
	
	
};
/**
 * 
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,Category="class defaults")
	TMap<ECharacterClass,FCharacterClassDefaultInfo> CharacterClassInfoMap;
	
	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect>SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect>VitalAttributes;

	UPROPERTY(EditDefaultsOnly,Category="common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;


	UPROPERTY(EditDefaultsOnly,Category="common Class Defaults|Damage")
	TObjectPtr<UCurveTable>DamagecalculationCoeffficient;
	
	FCharacterClassDefaultInfo GetCharacterClassInfo(ECharacterClass CharacterClass);

};
