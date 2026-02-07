// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AbilitySyste/Abilities/AuraDamageAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
class UGameplayEffect;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraDamageAbility
{
	GENERATED_BODY()

	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable,Category="ProjectileSpell")
	void SpawnProjectile(const FVector& ProjectileTargetLocation ,const FGameplayTag& SocketTage,bool bOverridePitch=false,float PitchOverride=0.f);

	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;
	
};
