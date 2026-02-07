// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Interaction/ModifierDependencyInterface.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged,int32/*StatValue*/)
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface,public IModifierDependencyInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet()const {return AttributeSet;}

	FORCEINLINE virtual FOnExternalGameplayModifierDependencyChange* GetOnModifierDependencyChanged() override { return &OnModifierDependencyChanged; }

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

	FOnPlayerStateChanged OnXPChangedDelegate;
	FOnPlayerStateChanged OnLevelChangedDelegate;
	FOnPlayerStateChanged OnAttributePointsChangeDelegate;
	FOnPlayerStateChanged OnSpellPointsChangeDelegate;

	FORCEINLINE int32 GetPlayerLevel()const{return Level;}
	FORCEINLINE int32 GetXP()const{return XP;}
	FORCEINLINE int32 GetAttributePoints()const{return AttributePoints;}
	FORCEINLINE int32 GetSpellPoints()const{return SpellPoints;}

	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);
	void AddToAttributePoints(int32 InAttributePoints);
	void AddToSpellPoints(int32 InSpellPoints);
	
	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	FOnExternalGameplayModifierDependencyChange OnModifierDependencyChanged;
	
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level)
	int32 Level=1;
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_XP)
	int32 XP=1;
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_AtttributePoints)
	int32 AttributePoints=0;
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints=1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	UFUNCTION()
	void OnRep_AtttributePoints(int32 OldAttributePoints);
	UFUNCTION()
	void OnRep_SpellPoints(int32  OldSpellPoints);
	
};
