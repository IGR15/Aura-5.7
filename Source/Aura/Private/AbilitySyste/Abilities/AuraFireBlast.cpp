// IGR1S


#include "AbilitySyste/Abilities/AuraFireBlast.h"

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
