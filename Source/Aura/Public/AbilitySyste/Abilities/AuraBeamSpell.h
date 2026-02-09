// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageAbility.h"
#include "AuraBeamSpell.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraBeamSpell : public UAuraDamageAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="Beam")
	float ScatTargetRadios=400.f;
	UFUNCTION(BlueprintCallable)
	void StoreMouseDataInfo(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariablesr();
	
	UFUNCTION(BlueprintCallable)
	void TraceFirstTarget(const FVector& BeamTargetLocation);
	
	UFUNCTION(BlueprintCallable)
	void StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets);
protected:
	UPROPERTY(BlueprintReadWrite,Category="Beam")
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite,Category="Beam")
	TObjectPtr<AActor> MouseHitActor;

	UPROPERTY(BlueprintReadWrite,Category="Beam")
	TObjectPtr<APlayerController>OwnerPlayerController;

	UPROPERTY(BlueprintReadWrite,Category="Beam")
	TObjectPtr<ACharacter>OwnerCharacter;
	
	UPROPERTY(EditDefaultsOnly,Category="Beam")
	int32 MaxNumShockTargets=5;

};
