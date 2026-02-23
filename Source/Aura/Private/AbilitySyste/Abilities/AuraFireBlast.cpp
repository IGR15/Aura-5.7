// IGR1S


#include "AbilitySyste/Abilities/AuraFireBlast.h"

#include "AbilitySyste/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const float ManaCost=FMath::Abs(GetManaCost(Level));

	
	int32 ScaledDamage =Damage.GetValueAtLevel(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
					// Title
					"<Title>FIRE BLAST</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
					//Number of Fire Balls
					"<Default>Launches %d </>"
					"<Default>fire balls in all directions,each coming back and  </>"
					"<Default>exploding upon return, ccausing</>"

					// Damage
					"<Damage>%d</><Default>radial fire damage with</>"
					"a chance to burn </>"),

					// Values
					Level,
					ManaCost,
					Cooldown,
					NumFireBalls,
					ScaledDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{

	const float ManaCost=FMath::Abs(GetManaCost(Level));

	
	int32 ScaledDamage =Damage.GetValueAtLevel(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
					// Title
					"<Title>Next Level</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
					//Number of Fire Balls
					"<Default>Launches %d </>"
					"<Default>fire balls in all directions,each coming back and  </>"
					"<Default>exploding upon return, ccausing</>"

					// Damage
					"<Damage>%d</><Default>radial fire damage with</>"
					"a chance to burn </>"),

					// Values
					Level,
					ManaCost,
					Cooldown,
					NumFireBalls,
					ScaledDamage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBals()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator>Rotators = UAuraAbilitySystemLibrary::EvenlySpaceDRotators(Forward,FVector::UpVector,360.f,NumFireBalls);
	
	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
		FDamageEffectParams DamageEffectParams= MakeDamageEffectParams();
		FireBall->DamageEffectParams = DamageEffectParams;
		
		FireBalls.Add(FireBall);
		
		FireBall->FinishSpawning(SpawnTransform);
	}
	
	return FireBalls;
}
