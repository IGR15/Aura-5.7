// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AbilitySyste/Abilities/AuraProjectileSpell.h"
#include "AuraFIreBolt.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFIreBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& ProjectileTargetLocation ,const FGameplayTag& SocketTage,bool bOverridePitch=false,float PitchOverride=0.f,AActor* HomingTarget=nullptr);

protected:
	UPROPERTY(EditDefaultsOnly,Category="FireBolt")
	float ProjectileSpread=90.f;

	UPROPERTY(EditDefaultsOnly,Category="FireBolt")
	int32 MaxNumProjectiles=5;

	UPROPERTY(EditDefaultsOnly,Category="FireBolt")
	float HomingAccelerationMin=1600.f;

	UPROPERTY(EditDefaultsOnly,Category="FireBolt")
	float HomingAccelerationMax=3200.f;

	UPROPERTY(EditDefaultsOnly,Category="FireBolt")
	bool bLaunchingHomingProjectile=true;
	
};
