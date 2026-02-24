// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageAbility.h"
#include "RainOfFire.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class AURA_API URainOfFire : public UAuraDamageAbility
{
	GENERATED_BODY()
	// AuraFireBlast.h
public:
	/*UFUNCTION(blueprintCallable)
	void SpawnFireRain(const FVector& SpawnCenter, float Radius, int32 TotalProjectiles);*/

	UFUNCTION(BlueprintCallable)
	void SpawnNextFireRain(const FVector& SpawnLocation);
	
	UFUNCTION(BlueprintCallable)
	static TArray<FVector> GetRandomPointsInRadius(const FVector& SpawnCenter,float Radius,int32 NumPoints,float ZOffset = 0.f) ;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAuraProjectile> FireBallClass;

	

	UPROPERTY(BlueprintReadOnly)
	FVector FireRainCenter;
	
	UPROPERTY(BlueprintReadOnly)
	float FireRainRadius = 0.f;
	
	UPROPERTY(BlueprintReadOnly)
	int32 FireRainTotal = 0;
	
	UPROPERTY(BlueprintReadOnly)
	int32 FireRainSpawned = 0;
};
