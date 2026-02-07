// IGR1S


#include "AbilitySyste/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)const
{
	int32 Level=1;
	bool bSearching=true;
	while (bSearching)
	{
		//levelupInfo[1]=level 1 Information
		//levelupInfo[2]=Level 1 information
		if (LevelUpInfo.Num()-1 <=Level)return Level;

		if (XP>= LevelUpInfo[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching=false;
		}
		
	}
	return Level;
}
