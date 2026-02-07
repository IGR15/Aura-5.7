// IGR1S


#include "UI/WidgetController/MenuWidgetController.h"
#include <utility>

#include "AbilitySyste/AuraAbilitySystemComponent.h"
#include "AbilitySyste/Data/AttributeInfo.h"
#include "AbilitySyste/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

void UMenuWidgetController::BroadCastInitValues()
{
	check(Attributeinfo);
	
	for (auto& Pair :GetAuraAS()->TagsToAttributes)
	{
		BroadCastAttributeInfo(Pair.Key,Pair.Value());
	}
	AttributePointsChangeDelegate.Broadcast(GetAuraPS()->GetAttributePoints());

	
}

void UMenuWidgetController::BindCallbacks()
{
	check(Attributeinfo);
	for (auto& Pair :GetAuraAS()->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair](const FOnAttributeChangeData& Data)
			{
				BroadCastAttributeInfo(Pair.Key,Pair.Value());
			}
		);
	}
	GetAuraPS()->OnAttributePointsChangeDelegate.AddLambda(
		[this](int32 Points)
	{
		AttributePointsChangeDelegate.Broadcast(Points);
	}
	);
}

void UMenuWidgetController::UpgradeAttributes(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC= CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttributes(AttributeTag);
}

void UMenuWidgetController::BroadCastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute)const
{
	FAuraAttributeInfo Info =Attributeinfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue=Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
	
}
