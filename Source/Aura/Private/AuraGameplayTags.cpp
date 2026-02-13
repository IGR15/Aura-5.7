// IGR1S

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"


FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitilizeNativeGameplayTags()
{
	//secondary Attributes
	GameplayTags.Attributes_Secondary_Armor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduces Damage Taken,Improves Block chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("Ignores Percentage of enemy armor, increases critical hit chance"));
	GameplayTags.Attributes_Secondary_BlockChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("chance to cut incoming damage in half"));
	GameplayTags.Attributes_Secondary_CriticalHitChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),FString("chance to double damage plus critical hit bonus"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("bonus damage added when a critical hit is scored"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("reduces critical hit chance of attacking enemies"));
	GameplayTags.Attributes_Secondary_HealthRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("amount of health regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("amount of mana regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_MaxHealth=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("max health"));
	GameplayTags.Attributes_Secondary_MaxMana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("max mana"));

	//Primary Attributes
	
	GameplayTags.Attributes_Primary_Strength=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("Increases Physical damage"));
	GameplayTags.Attributes_Primary_Intelligence=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("Increases  magical damage"));
	GameplayTags.Attributes_Primary_Resilience=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString("Increases Armor and Armor Penetration"));
	GameplayTags.Attributes_Primary_Vigor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("Increases Health"));

	//Meta
	GameplayTags.Attributes_Meta_IncomingXP=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"),FString("Incoming XP Meta Attribute"));

	//input

	GameplayTags.InputTag_LMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString("Input Tag for left Mouse Button"));
	GameplayTags.InputTag_RMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("Input Tag for 1 Key"));
	GameplayTags.InputTag_2=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),FString("Input Tag for 2 Key"));
	GameplayTags.InputTag_3=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),FString("Input Tag for 3 Key"));
	GameplayTags.InputTag_4=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),FString("Input Tag for 4 Key"));
	GameplayTags.InputTag_Passive_1=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.1"),FString("Input Tag for passive ability 1"));
	GameplayTags.InputTag_Passive_2=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.2"),FString("Input Tag for passive ability 2"));
	/*
	 * Damage Types
	 */
	GameplayTags.Damage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),FString("Damage"));
	GameplayTags.Damage_Fire=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"),FString("Fire Damage Type"));
	GameplayTags.Damage_Lightning=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"),FString("Lightning Damage Type"));
	GameplayTags.Damage_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"),FString("Arcane Damage Type"));
	GameplayTags.Damage_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"),FString("Physical Damage Type"));

	/*
	 * Damage Resistances 
	 */
	GameplayTags.Attributes_Resistance_Fire=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"),FString("Fire Resistance Damage Type"));
	GameplayTags.Attributes_Resistance_Lightning=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"),FString("Lightning Resistance Damage Type"));
	GameplayTags.Attributes_Resistance_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"),FString("Arcane Resistance Damage Type"));
	GameplayTags.Attributes_Resistance_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"),FString("Physical Resistance Damage Type"));

	/*
	 * Map of Damage Types to Resistances
	 */
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Fire,GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Lightning,GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Arcane,GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Physical,GameplayTags.Attributes_Resistance_Physical);
	/*
	 * Debuff Types
	 */
	GameplayTags.Debuff_Burn=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Brun"),FString("Fire Debuff"));
	GameplayTags.Debuff_Stun=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"),FString("Lightning Debuff"));
	GameplayTags.Debuff_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Arcane"),FString("Arcane Debuff"));
	GameplayTags.Debuff_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Physical"),FString("Physical Debuff"));
	
	GameplayTags.Debuff_Chance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"),FString("Chance to apply Debuff"));
	GameplayTags.Debuff_Damage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"),FString("amount of damage caused by the debuff"));
	GameplayTags.Debuff_Duration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"),FString("how long is the debuff"));
	GameplayTags.Debuff_Frequency=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"),FString("the frequency of the debuff"));

	/*
	 * Map of Damage types to Debuffs
	 */
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire,GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning,GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane,GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical,GameplayTags.Debuff_Physical);
	
	/*
	 * Effects
	 */
	GameplayTags.Effects_HitReact=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"),FString("Tag granted when Hit Reacting"));


	/*Abilities*/
	GameplayTags.Abilities_Attack=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"),FString("Attack ability Tag"));
	GameplayTags.Abilities_Summon=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"),FString("Summon ability Tag"));
	GameplayTags.Abilities_Fire_FireBolt=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"),FString("FireBolt ability Tag"));
	GameplayTags.Abilities_Lightning_Electrocute=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"),FString("Electrocute ability Tag"));

	GameplayTags.Abilities_None=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"),FString("No ability-like the nullptr for ability Tags"));


	
	GameplayTags.Abilities_HitReact=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.HitReact"),FString("Hit React Ability"));
	GameplayTags.Abilities_Status_Locked=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"),FString("locked Status tag"));
	GameplayTags.Abilities_Status_Eligible=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"),FString("Eligible Status tag"));
	GameplayTags.Abilities_Status_Unlocked=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"),FString("Unlocked Status tag"));
	GameplayTags.Abilities_Status_Equipped=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"),FString("Equipped Status tag"));

	GameplayTags.Abilities_Type_Offensive=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"),FString("Ability type Offensive "));
	GameplayTags.Abilities_Type_Passive=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"),FString("ability type Passive "));
	GameplayTags.Abilities_Type_None=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"),FString("ability type none "));



	/*Abilities Cooldown*/
	GameplayTags.Cooldown_Fire_FireBolt=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"),FString("FireBolt Cooldown ability Tag"));
	GameplayTags.Cooldown_Lightning_Electrocute=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Lightning.Electrocute"),FString("Electrocute Cooldown Ability Tag"));


	
	/*Sockets*/
	GameplayTags.CombatSocket_Weapon=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"),FString("Weapon"));
	GameplayTags.CombatSocket_RightHand=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"),FString("Right Hand"));
	GameplayTags.CombatSocket_LeftHand=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"),FString("left Hand"));
	GameplayTags.CombatSocket_Tail=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"),FString("Tail"));

	/*Montages*/
	GameplayTags.Montage_Attack_1=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"),FString("Attack 1"));
	GameplayTags.Montage_Attack_2=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"),FString("Attack 2"));
	GameplayTags.Montage_Attack_3=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"),FString("Attack 3"));
	GameplayTags.Montage_Attack_4=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"),FString("Attack 4"));

	/*
	 * Player Tags
	 */
	GameplayTags.Player_Block_InputPressed=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputPressed"),FString("Block input"));
	GameplayTags.Player_Block_InputHeld=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputHeld"),FString("Block input"));
	GameplayTags.Player_Block_InputReleased=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputReleased"),FString("Block input"));
	GameplayTags.Player_Block_CursorTrace=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.CursorTrace"),FString("Block CursorTrace under cursor"));

	GameplayTags.Abilities = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities"), FString("Ability Tag."));
	GameplayTags.Abilities_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive"), FString("Passive Ability Tag."));
}
