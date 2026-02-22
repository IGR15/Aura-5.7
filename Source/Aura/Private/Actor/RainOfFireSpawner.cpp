// IGR1S


#include "Actor/RainOfFireSpawner.h"
#include "NiagaraFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "NiagaraSystem.h"
#include "TimerManager.h"

ARainOfFireSpawner::ARainOfFireSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARainOfFireSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ARainOfFireSpawner::StartRain(
	const FVector& InCenter,
	float InRadius,
	int32 InTotalFireballs,
	float InSpawnHeight,
	float InDuration)
{
	Center = InCenter;
	Radius = InRadius;
	SpawnHeight = InSpawnHeight;
	TotalFireballs = InTotalFireballs;
	SpawnedFireballs = 0;

	if (InDuration > 0.f)
	{
		SpawnInterval = InDuration / FMath::Max(1, TotalFireballs);
	}

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ARainOfFireSpawner::SpawnSingleFireball,
		SpawnInterval,
		true
	);
}

void ARainOfFireSpawner::SpawnSingleFireball()
{
	if (SpawnedFireballs >= TotalFireballs)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		Destroy();
		return;
	}

	const FVector SpawnLocation = GenerateRandomPointInCircle();
	DrawDebugSphere(
			GetWorld(),
			SpawnLocation,
			50.f,        // Radius of sphere
			12,          // Segments (higher = smoother)
			FColor::Red, // Color
			false,       // Persistent lines
			2.f          // Lifetime (seconds)
		);
	if (FireballSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			FireballSystem,
			SpawnLocation,
			FRotator(-90.f, 0.f, 0.f)
		);
	}

	SpawnedFireballs++;
}

FVector ARainOfFireSpawner::GenerateRandomPointInCircle() const
{
	const float RandomAngle = FMath::FRandRange(0.f, 2.f * PI);
	const float RandomRadius = Radius * FMath::Sqrt(FMath::FRand());

	const float X = RandomRadius * FMath::Cos(RandomAngle);
	const float Y = RandomRadius * FMath::Sin(RandomAngle);

	FVector Location = Center + FVector(X, Y, 0.f);
	Location.Z += SpawnHeight;

	return Location;
}

