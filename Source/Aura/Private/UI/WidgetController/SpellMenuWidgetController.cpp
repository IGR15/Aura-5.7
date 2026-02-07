// IGR1S


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySyste/AuraAbilitySystemComponent.h"
#include "AbilitySyste/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadCastInitValues()
{
	BroadCastAbilityInfo();
	SpellPointsChanged.Broadcast(GetAuraPS()->GetSpellPoints());
	
}

void USpellMenuWidgetController::BindCallbacks()
{
	GetAuraASC()->AbilityStatusChangeDelegate.AddLambda(
		[this](const FGameplayTag& AbilityTag,const FGameplayTag& StatusTag,int32 NewLevel)
		{
			if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
			{
				SelectedAbility.Status = StatusTag;
				bool bEnableSpendPoints=false;
				bool bEnableEquip=false;
				ShouldEnableButtons(StatusTag,CurrentSpellPoints,bEnableSpendPoints,bEnableEquip);
				FString Description;
				FString NextLevelDescription;
				GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag,Description,NextLevelDescription);
				SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints,bEnableEquip,Description,NextLevelDescription);
				
			}
			if (AbilityInfo)
			{
				FAuraAbilityInfo Info=AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag=StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}
	);
	GetAuraASC()->AbilityEquippedDelegate.AddUObject(this,&USpellMenuWidgetController::OnAbilityEquipped);

	GetAuraPS()->OnSpellPointsChangeDelegate.AddLambda([this](int32 SpellPoints)
	{
		SpellPointsChanged.Broadcast(SpellPoints);
		CurrentSpellPoints=SpellPoints;

		bool bEnableSpendPoints=false;
		bool bEnableEquip=false;
		ShouldEnableButtons(SelectedAbility.Status,CurrentSpellPoints,bEnableSpendPoints,bEnableEquip);
		FString Description;
		FString NextLevelDescription;
		GetAuraASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability,Description,NextLevelDescription);
		SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints,bEnableEquip,Description,NextLevelDescription);
	});
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	if (bWaitForEquipSelection)
	{
		const FGameplayTag AbilityType=AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType;
		StopWaitingForEquipDelegate.Broadcast(AbilityType);
		bWaitForEquipSelection=false;
	}
	const FAuraGameplayTags GameplayTags=FAuraGameplayTags::Get();
	const int32 SpellPoints=GetAuraPS()->GetSpellPoints();
	FGameplayTag AbilityStatus;
	
	const bool bTagValid=AbilityTag.IsValid();
	const bool bTagNone=AbilityTag.MatchesTag(GameplayTags.Abilities_None);

	FGameplayAbilitySpec* AbilitySpec=GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	
	const  bool bSpecValid=AbilitySpec!=nullptr;
	if (!bTagValid|| bTagNone|| !bSpecValid)
	{
		AbilityStatus=GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus=GetAuraASC()->GetStatusTagFromSpec(*AbilitySpec);
	}
	SelectedAbility.Ability=AbilityTag;
	SelectedAbility.Status=AbilityStatus;
	bool bEnableSpendPoints=false;
	bool bEnableEquip=false;
	ShouldEnableButtons(AbilityStatus,SpellPoints,bEnableSpendPoints,bEnableEquip);
	FString Description;
	FString NextLevelDescription;
	GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag,Description,NextLevelDescription);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints,bEnableEquip,Description,NextLevelDescription);
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	if (GetAuraASC())
	{
		GetAuraASC()->ServerSpendSpellPoints(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::GlobeDeselect()
{
	if (bWaitForEquipSelection)
	{
		const FGameplayTag AbilityType=AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitingForEquipDelegate.Broadcast(AbilityType);
		bWaitForEquipSelection=false;
	}
	SelectedAbility.Ability=FAuraGameplayTags::Get().Abilities_None;
	SelectedAbility.Status=FAuraGameplayTags::Get().Abilities_Status_Locked;
	SpellGlobeSelectedDelegate.Broadcast(false,false,FString(),FString());
}

void USpellMenuWidgetController::EquipButtonPressed()
{
	const FGameplayTag AbilityType= AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;

	WaitForEquipSelectionDelegate.Broadcast(AbilityType);
	bWaitForEquipSelection=true;

	const FGameplayTag SelectedStatus=GetAuraASC()->GetStatusFromAbilityTag(SelectedAbility.Ability);
	if (SelectedStatus.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped))
	{
		SelectedSlot=GetAuraASC()->GetInputTagFromAbilityTag(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType)
{
	if (!bWaitForEquipSelection)return;
	//Check Selected ability against the slot's ability type.
	//(don't equip an offensive spell in a passive slot and vise versa)

	const FGameplayTag& SelectedAbilityType=AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
	if (!SelectedAbilityType.MatchesTagExact(AbilityType))return;

	
	GetAuraASC()->ServerEquipAbility(SelectedAbility.Ability,SlotTag);
}

void USpellMenuWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PrevSlot)
{
	bWaitForEquipSelection=false;

	const FAuraGameplayTags& GameplayTags=FAuraGameplayTags::Get();
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag=GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag=PrevSlot;
	LastSlotInfo.AbilityTag=GameplayTags.Abilities_None;
	// BroadCast empty INfo if PreviousSlot is a Valid slot. only if equipping an already-equipped spell
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo Info=AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag=Status;
	Info.InputTag=Slot;
	AbilityInfoDelegate.Broadcast(Info);

	StopWaitingForEquipDelegate.Broadcast(AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType);
	SpellGlobeReassignedDelegate.Broadcast(AbilityTag);
	GlobeDeselect();
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,
                                                     bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	const FAuraGameplayTags GameplayTags=FAuraGameplayTags::Get();
	bShouldEnableSpellPointsButton=false;
	bShouldEnableEquipButton=false;


	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButton=true;
		if (SpellPoints>0)
		{
			bShouldEnableSpellPointsButton=true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints>0)
		{
			bShouldEnableSpellPointsButton=true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton=true;
		if (SpellPoints>0)
		{
			bShouldEnableSpellPointsButton=true;
		}
	}
	

}
