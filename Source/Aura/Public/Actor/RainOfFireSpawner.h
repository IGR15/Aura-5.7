// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RainOfFireSpawner.generated.h"

class UNiagaraSystem;

UCLASS()
class AURA_API ARainOfFireSpawner : public AActor
{
	GENERATED_BODY()

public:
	ARainOfFireSpawner();

	// Call this to start the rain
	
	void StartRain(
		const FVector& InCenter,
		float InRadius,
		int32 InTotalFireballs,
		float InSpawnHeight,
		float InDuration);

protected:
	virtual void BeginPlay() override;

	void SpawnSingleFireball();
	FVector GenerateRandomPointInCircle() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Rain")
	UNiagaraSystem* FireballSystem;

	UPROPERTY(EditDefaultsOnly, Category="Rain")
	float SpawnInterval = 0.1f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector Center;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Radius = 1000.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SpawnHeight = 1500.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 TotalFireballs = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SpawnedFireballs = 0;

	FTimerHandle SpawnTimerHandle;

private:

	
};