// IGR1S


#include "AbilitySyste/Abilities/RainOfFire.h"

#include "AbilitySyste/Abilities/AuraFireBlast.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

/*void URainOfFire::SpawnFireRain(const FVector& SpawnCenter, float Radius, int32 TotalProjectiles)
{
	// Authority gate
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	if (!FireBallClass) return;

	FireRainCenter = SpawnCenter;
	FireRainRadius = Radius;
	FireRainTotal = TotalProjectiles;
	FireRainSpawned = 0;

	// Start immediately
	SpawnNextFireRain();
	
}*/

void URainOfFire::SpawnNextFireRain(const FVector& SpawnLocation)
{
	

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);

	

	AAuraProjectile* FireBall = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		FireBallClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		CurrentActorInfo->PlayerController->GetPawn(),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (FireBall)
	{
		FDamageEffectParams DamageParams = MakeDamageEffectParams();
		FireBall->DamageEffectParams = DamageParams;
		FireBall->SetOwner(GetAvatarActorFromActorInfo());

		FireBall->FinishSpawning(SpawnTransform);

		// Force downward velocity (rain effect)
		if (FireBall->ProjectileMovement)
		{
			FireBall->ProjectileMovement->Velocity = FVector(0.f, 0.f, -1.f) * 
				FireBall->ProjectileMovement->InitialSpeed;

			FireBall->ProjectileMovement->ProjectileGravityScale = 1.f; 
		}
	}
	
}

TArray<FVector> URainOfFire::GetRandomPointsInRadius(const FVector& SpawnCenter, float Radius, int32 NumPoints,
	float ZOffset) 
{
	TArray<FVector> Points;
	Points.Reserve(NumPoints);

	for (int32 i = 0; i < NumPoints; ++i)
	{
		// Uniform distribution inside circle
		const float Angle = FMath::FRandRange(0.f, 2.f * PI);
		const float Distance = FMath::Sqrt(FMath::FRand()) * Radius;

		const float X = FMath::Cos(Angle) * Distance;
		const float Y = FMath::Sin(Angle) * Distance;

		FVector Location = SpawnCenter + FVector(X, Y, ZOffset);
		Points.Add(Location);
	}

	return Points;
}
