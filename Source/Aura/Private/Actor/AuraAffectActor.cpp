// IGR1S


#include "Actor/AuraAffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AAuraAffectActor::AAuraAffectActor()
{
 	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent( CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}




void AAuraAffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AAuraAffectActor::ApplyEffictToActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	//you can do all of this in blueprint

	const bool bIsEnemy=TargetActor->ActorHasTag(FName("Enemy"));
	if (bIsEnemy && !bApplyEffectsToEnemies)return;
	
	UAbilitySystemComponent* TargetAbilitySystemComponent= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAbilitySystemComponent==nullptr)return;
	check(GamePlayEffectClass);
	
	// a handel is a light wight wrapper that handles context and its data 
	FGameplayEffectContextHandle EffectContextHandle= TargetAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	//this is also a Wrapper that holds the effectSpec
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GamePlayEffectClass,ActorLevel,EffectContextHandle);
	
	FActiveGameplayEffectHandle ActiveEffectHandle= TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// to store in the map
	const bool bIsInfinite= EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy== EGameplayEffectDurationType::Infinite;
	
	if (bIsInfinite && InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		const auto UID = TargetActor->GetUniqueID();
		ActiveInfiniteEffects.Add(UID, ActiveEffectHandle);
	}
	if (!bIsInfinite)
	{
		Destroy();
	}
}

void AAuraAffectActor::OnOverlap(AActor* TargetActor)
{
	const bool bIsEnemy=TargetActor->ActorHasTag(FName("Enemy"));
	if (bIsEnemy && !bApplyEffectsToEnemies)return;
	
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffictToActor(TargetActor, InsantGampelayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffictToActor(TargetActor, DurationGampelayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffictToActor(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAuraAffectActor::OnEndverlap(AActor* TargetActor)
{
	const bool bIsEnemy=TargetActor->ActorHasTag(FName("Enemy"));
	if (bIsEnemy && !bApplyEffectsToEnemies)return;
	
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffictToActor(TargetActor, InsantGampelayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffictToActor(TargetActor, DurationGampelayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffictToActor(TargetActor,InfiniteGameplayEffectClass);
		
	}
	if (InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		//online
		const auto UID = TargetActor->GetUniqueID();
		if (!ActiveInfiniteEffects.Contains(UID)) return;
 
		const auto &EffectHandle = ActiveInfiniteEffects[UID];
		if (!TargetASC->RemoveActiveGameplayEffect(EffectHandle, 1)) return;
 
		ActiveInfiniteEffects.Remove(UID);
		//this is easyer than the loop but on multipule overlaping it wont stack 
		// if (TargetASC)
		// {
		// 	TargetASC->RemoveActiveGameplayEffectBySourceEffect(InfiniteGameplayEffectClass,TargetASC,1);
		// }
		
		/*
			long way to remove infinite effect 
			if (!IsValid(TargetASC))return;
			
			 TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			
			 for (auto HandlePair : AcitveEffectHandles)
			{
				if (TargetASC==HandlePair.Value)
					{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
						HandlesToRemove.Add(HandlePair.Key);
		 			}
			}
			for (auto& Handle : HandlesToRemove)
			{
		 		AcitveEffectHandles.FindAndRemoveChecked(Handle);
			}
		*/
	}
}



