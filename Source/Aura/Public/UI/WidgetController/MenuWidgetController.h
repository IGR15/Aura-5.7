// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "MenuWidgetController.generated.h"

struct FGameplayAttribute;
struct FGameplayTag;
class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&,Info);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadCastInitValues()override;
	virtual void BindCallbacks()override;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnPlayerStatChangeSignature AttributePointsChangeDelegate;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

	UFUNCTION(BlueprintCallable)
	void UpgradeAttributes(const FGameplayTag& AttributeTag);

private:
	void  BroadCastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute)const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GAS|Attributes")
	TObjectPtr<UAttributeInfo>Attributeinfo;
};
