// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelectedButton);

class UMVVM_LoadSlot;
/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	void InitiateLoadScreen();
	
	UPROPERTY(BlueprintAssignable)
	FSlotSelectedButton SlotSelectedDelegate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot>LoadSlotViewModelClass;
	
	UFUNCTION(blueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelIndex(int32 Index) const ;
	
	UFUNCTION(BlueprintCallable)
	void NewSlotButtonPressed(int32 Slot,const FString& EnteredName);
	
	UFUNCTION(BlueprintCallable)
	void NewGameButtonPressed(int32 Slot);
	
	UFUNCTION(BlueprintCallable)
	void SelectSlotButtonPressed(int32 Slot);
	
	UFUNCTION(BlueprintCallable)
	void DeleteButtonPressed();
	
	UFUNCTION(BlueprintCallable)
	void PlayButtonPressed();
	
	void LoadData();
	
	void SetNumLoadSlots(int32 InNumLoadSlots);
	
	int32 GetNumLoadSlots()const {return NumLoadSlots;}
	
	
	
private:
	
	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> SelectedLoadSlot;
	
	UPROPERTY(Transient)
	TMap<int32,TObjectPtr<UMVVM_LoadSlot>> LoadSlots;
	
	UPROPERTY(Transient)
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_0;
	
	UPROPERTY(Transient)
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_1;
	
	UPROPERTY(Transient)
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_2;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess="true"))
	int32 NumLoadSlots;
	
	
};
