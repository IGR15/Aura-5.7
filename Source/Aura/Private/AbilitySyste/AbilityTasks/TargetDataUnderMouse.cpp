// IGR1S


#include "AbilitySyste/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "Aura/Aura.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj=NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallControlled=Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallControlled)
	{
		SendCursorData();
	}
	else
	{
		//on the server
		const FGameplayAbilitySpecHandle SpecHandle=GetAbilitySpecHandle();
		const FPredictionKey PredictionKey=GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle,
			PredictionKey).AddUObject(this,&UTargetDataUnderMouse::OntargetDataPeplicatedCallback);

		const bool bCalledDelegat = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle,PredictionKey);
		if (!bCalledDelegat)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	
	
}

void UTargetDataUnderMouse::SendCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	FGameplayAbilityTargetData_SingleTargetHit* Data=new FGameplayAbilityTargetData_SingleTargetHit();
	APlayerController* PC= Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CurserHit;
	PC->GetHitResultUnderCursor(ECC_Visibility,false,CurserHit);
	FGameplayAbilityTargetDataHandle DataHandle;
	Data->HitResult=CurserHit;
	DataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
		);
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OntargetDataPeplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
