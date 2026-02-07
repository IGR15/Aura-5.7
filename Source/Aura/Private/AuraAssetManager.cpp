// IGR1S


#include "AuraAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine)
	UAuraAssetManager* AuraAssetManager=Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitilizeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();//this initilizes target data ( InitTargetDataScriptStructCache())
	
	
}
