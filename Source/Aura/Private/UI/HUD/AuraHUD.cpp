// IGR1S


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/MenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/SpellMenuWidgetController.h"

// Returns the overlay widget controller, creating it if necessary
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		// Instantiate widget controller using UClass reference set in Blueprint
		OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		// Inject external references (PlayerState, ASC, AttributeSet)
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		// Bind attribute change callbacks to delegates
		OverlayWidgetController->BindCallbacks();

		
	}
	return OverlayWidgetController;
}

UMenuWidgetController* AAuraHUD::GetMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController=NewObject<UMenuWidgetController>(this,AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacks();
	}
	return AttributeMenuWidgetController;
}

USpellMenuWidgetController* AAuraHUD::GetSpellMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (SpellMenuWidgetController == nullptr)
	{
		SpellMenuWidgetController=NewObject<USpellMenuWidgetController>(this,SpellMenuWidgetControllerClass);
		SpellMenuWidgetController->SetWidgetControllerParams(WCParams);
		SpellMenuWidgetController->BindCallbacks();
	}
	return SpellMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// Safety check — ensures widget class is set in BP_AuraHUD
	checkf(OverlayWidgetClass,TEXT("overlay widget class uninitialized , please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("overlay widget controller class uninitialized , please fill out BP_AuraHUD "))

	// Create the actual overlay widget instance in the world
	UUserWidget* Widget= CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget=Cast<UAuraUserWidget>(Widget);
	
	// Build struct containing required controller parameters
	const FWidgetControllerParams WCParams(PC,PS,ASC,AS);
	// Retrieve or construct the overlay widget controller
	UOverlayWidgetController* WidgetController=GetOverlayWidgetController(WCParams);
	
	// Set the controller reference inside the overlay widget
	OverlayWidget->SetWidgetController(WidgetController);
	// Push initial values from attribute set to UI
	WidgetController->BroadCastInitValues();
	// Add widget to screen
	Widget->AddToViewport();
	
}


