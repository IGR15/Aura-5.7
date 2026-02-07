// IGR1S


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySyste/AuraAbilitySystemComponent.h"
#include "AbilitySyste/AuraAttributeSet.h"
#include "AbilitySyste/Data/AbilityInfo.h"
#include "AbilitySyste/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadCastInitValues()
{
	// Force-cast the generic AttributeSet to your custom AuraAttributeSet

	// Broadcast initial health values to binded UMG widgets
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());

	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacks()
{
	GetAuraPS()->OnXPChangedDelegate.AddUObject(this,&UOverlayWidgetController::OnXPChanged);
	// Cast base attribute set to the specific AuraAttributeSet subclass

	AuraPlayerState->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel)
		{
			OnPlayerLevelChangeDelegate.Broadcast(NewLevel);
		}
		);

	// Subscribe Health attribute changes to OnHealthChanged delegate
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	// Subscribe MaxHealth attribute changes to OnMaxHealthChanged delegate
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
			);
	

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
			);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
			
			
		);
	if (GetAuraASC())
	{
		GetAuraASC()->AbilityEquippedDelegate.AddUObject(this,&UOverlayWidgetController::OnAbilityEquipped);
		if (GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadCastAbilityInfo();
		}
		else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this,&UOverlayWidgetController::BroadCastAbilityInfo);

		}
		GetAuraASC()->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTages /* this is the input parameter*/ )
			{
				for (const FGameplayTag& Tag : AssetTages)
				{
					FGameplayTag MessageTag =FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row= GetDataTableRowByTag<FUIWidgetRow>(MessageDataTable,Tag);
						MessageWidgetRowDelegat.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnXPChanged(int32 NewXp)
{
	const ULevelUpInfo* LevelUpInfo =GetAuraPS()->LevelUpInfo;

	checkf(LevelUpInfo,TEXT("Unabled to find levelupinfo. fill out auraplayerstate Blueprint"));

	const int32 Level=LevelUpInfo->FindLevelForXP(NewXp);
	const int32 MaxLevel=LevelUpInfo->LevelUpInfo.Num()-1;

	if (Level<=MaxLevel&&Level>0)
	{

		const int32 LevelUpReq=LevelUpInfo->LevelUpInfo[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement=LevelUpInfo->LevelUpInfo[Level-1].LevelUpRequirement;

		const int32 DeltaLevelReq=LevelUpReq-PreviousLevelUpRequirement;
		const int32 XPForThisLevel=NewXp- PreviousLevelUpRequirement;

		const float XPBarPercent=static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelReq);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
		
	}

}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PrevSlot)
{

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

}

