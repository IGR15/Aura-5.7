// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"


struct FGameplayTag;
struct FDamageEffectParams;
class UAbilityInfo;
class AAuraHUD;
struct FWidgetControllerParams;
class USpellMenuWidgetController;
struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;
class UMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "AuraAbilitySystemLibrary|Debuff Data")
	static TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> GetDebuffTagToEffectMap(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController",meta=(DefaultToSelf="WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject,FWidgetControllerParams& OutWCParams,AAuraHUD*& OutAuraHUd);

	
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController",meta=(DefaultToSelf="WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController",meta=(DefaultToSelf="WorldContextObject"))
	static UMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController",meta=(DefaultToSelf="WorldContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);

	//this will initialize base attributes based on attribute class and lvl
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Character Class Defaultes")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass,float level,UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Character Class Defaultes")
	static void GiveStartupAbilites(const UObject* WorldContextObject,UAbilitySystemComponent* ASC,ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Character Class Defaultes")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Character Class Defaultes",meta=(DefaultToSelf="WorldContextObject"))
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static bool IsSuccessfullDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static float GetDebuffDurtaion(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static bool IsNotFriend(AActor* FirstActor,AActor* SecondActor);



	/*becase we are passing in a none const refrence the engine thinks its an output pin
	 * but we need the effectcontexthandle to be in input pin so we used UPARAM(ref) to tell the engine its an
	 * input pin 
	 */
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetIsBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle,bool bInIsBlockHit);
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,bool bInSuccessfulDebuff);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,float InDebuffDamage);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,float InDebuffDuration);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,float InDebuffFrequency);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,const FGameplayTag& InDamageType);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,const FVector& InImpulse);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Effects")
	static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,const FVector& InForce);

	
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Mechanics")
	static void GetLivePlayersWithInRadius(const UObject* WorldContextObject,TArray<AActor*>& OutOverlappingActors,const TArray<AActor*>& ActorsToIgnore,float Radius,const FVector& SphereOrigin);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Mechanics")
	static void GetClosestTargets(int32 MaxTargets,const TArray<AActor*>& Actors,TArray<AActor*>& OutClosestTargets,const FVector& Origin);
	
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject,ECharacterClass CharacterClass,int32 CharacterLevel);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Mechanics")
	static TArray<FRotator>EvenlySpaceDRotators(const FVector& Forward,const FVector& Axis,float Spread,int32 NumRotators);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Gameplay Mechanics")
	static TArray<FVector>EvenlyRotatedVectors(const FVector& Forward,const FVector& Axis,float Spread,int32 NumVectors);
	
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|Damage Effect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
};



