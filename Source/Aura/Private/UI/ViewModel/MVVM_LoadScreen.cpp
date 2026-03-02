// IGR1S


#include "UI/ViewModel/MVVM_LoadScreen.h"

#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadScreen::InitiateLoadScreen()
{
	if (!LoadSlotViewModelClass)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadSlotViewModelClass is NULL"));
	}
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_0->SetLoadSlotName(TEXT("LoadSlot_0"));
	LoadSlots.Add(0,LoadSlot_0);
	
	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_1->SetLoadSlotName(TEXT("LoadSlot_1"));
	LoadSlots.Add(1,LoadSlot_1);
	
	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_2->SetLoadSlotName(TEXT("LoadSlot_2"));
	LoadSlots.Add(2,LoadSlot_2);
	
}

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadScreen::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
	/*AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LoadSlots[Slot]->PlayerName = EnteredName;
	
	AuraGameModeBase->SaveSlotData(LoadSlots[Slot],Slot);
	LoadSlots[Slot]->InitializeSlot();*/
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UMVVM_LoadSlot* SlotVM = LoadSlots.FindRef(Slot);

	if (!IsValid(SlotVM))
	{
		UE_LOG(LogTemp, Error, TEXT("SlotVM INVALID. Slot=%d Ptr=%p"), Slot, SlotVM);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("SlotVM OK. Slot=%d Ptr=%p Name=%s"),
		   Slot, SlotVM, *SlotVM->GetLoadSlotName());

	SlotVM->PlayerName = EnteredName;
	AuraGameModeBase->SaveSlotData(SlotVM, Slot);
	SlotVM->InitializeSlot();
}

void UMVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndexDelegate.Broadcast(1);
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{
}
