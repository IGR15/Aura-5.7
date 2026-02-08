// IGR1S


#include "AbilitySyste/Abilities/AuraFIreBolt.h"

#include "AbilitySyste/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

FString UAuraFIreBolt::GetDescription(int32 Level)
{
	
	const float ManaCost=FMath::Abs(GetManaCost(Level));

	
	int32 ScaledDamage =Damage.GetValueAtLevel(Level);
	const float Cooldown = GetCoolDown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
					// Title
					"<Title>FIRE BOLT</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
					"<Default>Launches a bolt of fire, "
					"exploding on impact and dealing: </>"

					// Damage
					"<Damage>%d</><Default> fire damage with"
					" a chance to burn</>"),

					// Values
					Level,
					ManaCost,
					Cooldown,
					ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
					// Title
					"<Title>FIRE BOLT</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

					// Number of FireBolts
					"<Default>Launches %d bolts of fire, "
					"exploding on impact and dealing: </>"

					// Damage
					"<Damage>%d</><Default> fire damage with"
					" a chance to burn</>"),

					// Values
					Level,
					ManaCost,
					Cooldown,
					FMath::Min(Level, NumProjectiles),
					ScaledDamage);
	}
}

FString UAuraFIreBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL: </>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of FireBolts
			"<Default>Launches %d bolts of fire, "
			"exploding on impact and dealing: </>"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScaledDamage);
}

void UAuraFIreBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTage,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer=GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)return;
	const FVector SocketLocation=ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),
		SocketTage);
	//const FVector SocketLocation=CombatInterface->Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());
	FRotator Rotation=(ProjectileTargetLocation - SocketLocation).Rotation();
		
	if (bOverridePitch) Rotation.Pitch+=PitchOverride;

	const FVector Forward=Rotation.Vector();
	int32 EffectiveNumProjectiles=FMath::Min(NumProjectiles,GetAbilityLevel());
	TArray<FRotator>Rotations=UAuraAbilitySystemLibrary::EvenlySpaceDRotators(Forward,FVector::UpVector,ProjectileSpread,EffectiveNumProjectiles);
	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());
		AAuraProjectile* Projectile=GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	
		Projectile->DamageEffectParams=MakeDamageEffectParams();
		if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
		{
			Projectile->ProjectileMovement->HomingTargetComponent=HomingTarget->GetRootComponent();
		}
		else
		{
			/*
			 *Projectile->ProjectileMovement->HomingTargetComponent=NewObject<USceneComponent>(USceneComponent::StaticClass());
			 * when the projectile Dies and the HomingTargetComponent Go's out of scope the new Object dosent get marked for garbage collection and wont be cleaned up
			 * thats why we gave aura projectile a USceneComponent Variable ->HomingTargetSceneComponent
			 * and gave it a UPROPERTY() to mark it for garbage collection 
			 */  
			Projectile->HomingTargetSceneComponent=NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent=Projectile->HomingTargetSceneComponent;
			
		}

		Projectile->ProjectileMovement->HomingAccelerationMagnitude=FMath::RandRange(HomingAccelerationMin,HomingAccelerationMax);
		Projectile->ProjectileMovement->bIsHomingProjectile=bLaunchingHomingProjectile;
		Projectile->FinishSpawning(SpawnTransform);
	}
	
}

