// IGR1S


#include "AbilitySyste/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const float ManaCost=FMath::Abs(GetManaCost(Level));

	
	int32 ScaledDamage =Damage.GetValueAtLevel(Level);
	const float Cooldown = GetCoolDown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
					// Title
					"<Title>ELECTROCUTE</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
					"<Default>Emits a beam of Lightning, "
					"connecting with the target, repeatedly causing </>"

					// Damage
					"<Damage>%d</><Default> Lightning damage with"
					" a chance to Stun</>"),

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
					"<Title>ELECTROCUTE</>\n\n"

					// Level
					"<Small>Level: </><Level>%d</>\n"
					// ManaCost
					"<Small>ManaCost: </><ManaCost>%.1f</>\n"
					// Cooldown
					"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

					// Number of ShockTargets
					"<Default>Emits a beam of Lightning, "
					"Propagating to %d additional targets nearby, causing: </>"

					// Damage
					"<Damage>%d</><Default> Lightning damage with"
					" a chance to Stun</>"),

					// Values
					Level,
					ManaCost,
					Cooldown,
					FMath::Min(Level, MaxNumShockTargets -1 ),
					ScaledDamage);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	// Title
			"<Title>NEXT LEVEL</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of ShockTargets
			"<Default>Emits a beam of Lightning, "
			"Propagating to %d additional targets nearby, causing: </>"

			// Damage
			"<Damage>%d</><Default> Lightning damage with"
			" a chance to Stun</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets -1),
			ScaledDamage);
}
