// IGR1S


#include "AbilitySyste/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const float ManaCost=FMath::Abs(GetManaCost(Level));

	
	int32 ScaledDamage =Damage.GetValueAtLevel(Level);
	const float Cooldown = GetCoolDown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
					// Title
					"<Title>ARCANE SHARDS</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
					"<Default>Summon shard of Arcane Energy, "
					"causing radial Damage of: </>"

					// Damage
					"<Damage>%d</><Default> at the shard Origin</>"),

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
					"<Title>ARCANE SHARDS</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

					// Number of FireBolts
					"<Default>Summon %d Shards of Arcane Energy, "
					"causing radial Arcane damage: </>"

					// Damage
					"<Damage>%d</><Default> at the shard Origins</>"),

					// Values
					Level,
					ManaCost,
					Cooldown,
					FMath::Min(Level, MaxNumberOfShards ),
					ScaledDamage);
	}
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
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

			// Number of FireBolts
			"<Default>Summon %d Shards of Arcane Energy, "
			"causing radial Arcane damage: </>"

			// Damage
			"<Damage>%d</><Default> Arcane Damage</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumberOfShards ),
			ScaledDamage);
}
