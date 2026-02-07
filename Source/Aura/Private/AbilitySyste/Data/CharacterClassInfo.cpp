// IGR1S


#include "AbilitySyste/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetCharacterClassInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInfoMap.FindChecked(CharacterClass);
}
