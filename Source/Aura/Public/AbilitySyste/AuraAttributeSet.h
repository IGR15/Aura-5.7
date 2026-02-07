// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include  "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties();
	UPROPERTY()
	UAbilitySystemComponent* SourceASC=nullptr;
	UPROPERTY()
	UAbilitySystemComponent* TargetAsc=nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor=nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor=nullptr;
	UPROPERTY()
	AController* TargetController=nullptr;
	UPROPERTY()
	AController* SourceController=nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter=nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter=nullptr;
	
	FGameplayEffectContextHandle EffectContextHandle;
	
};
/***
 * created an alias to replace the long syntax
 * typedef is specific to the FGamePlayAttribute() signature, but TStaticFuncPtr is generic to any signature chosen
 */
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;

template<class T>
using TStaticFuncPtr=typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	void MaximizeVitalAttributes();
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	// virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)override;


	//this is called Function Pointers
	TMap<FGameplayTag,TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	//TMap<FGameplayTag,FAttributeFuncPtr> TagsToAttributes;
	//TMap<FGameplayTag,FGameplayAttribute(*)()> TagsToAttributes;
	//TMap<FGameplayTag,TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr> TagsToAttributes;

	//TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FunctionPointer;
	/*
	 * Primary Attributes 
	 */
	UPROPERTY(BlueprintReadOnly,Category="Primary Aattributes",ReplicatedUsing= OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,Strength);

	UPROPERTY(BlueprintReadOnly,Category="Primary Aattributes",ReplicatedUsing= OnRep_Intelligence )
	FGameplayAttributeData Intelligence ;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,Intelligence );

	UPROPERTY(BlueprintReadOnly,Category="Primary Aattributes",ReplicatedUsing= OnRep_Resilience)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,Resilience);

	UPROPERTY(BlueprintReadOnly,Category="Primary Aattributes",ReplicatedUsing= OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,Vigor);

	/*
	* Vital Attributes 
	*/	
	
	UPROPERTY(BlueprintReadOnly,Category="Vital Aattributes",ReplicatedUsing= OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,Health);
	

	
	
	UPROPERTY(BlueprintReadOnly,Category="Vital Aattributes",ReplicatedUsing= OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,Mana);
	
	

	/*
	* Secondary Attributes 
	*/	

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,Armor);

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,ArmorPenetration);

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,BlockChance);

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,CriticalHitChance);

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,HealthRegeneration);

	UPROPERTY(BlueprintReadOnly,Category="Secondary Aattributes",ReplicatedUsing= OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,ManaRegeneration);

	UPROPERTY(BlueprintReadOnly,Category="Vital Aattributes",ReplicatedUsing= OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,MaxHealth);

	UPROPERTY(BlueprintReadOnly,Category="Vital Aattributes",ReplicatedUsing= OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,MaxMana);

	/*
	 * Resistance Attributes 
	 */
	UPROPERTY(BlueprintReadOnly,Category="Resistance Aattributes",ReplicatedUsing= OnRep_FireResistance)
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,FireResistance);

	UPROPERTY(BlueprintReadOnly,Category="Resistance Aattributes",ReplicatedUsing= OnRep_LightningResistance)
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,LightningResistance);

	UPROPERTY(BlueprintReadOnly,Category="Resistance Aattributes",ReplicatedUsing= OnRep_ArcaneResistance)
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,ArcaneResistance);

	UPROPERTY(BlueprintReadOnly,Category="Resistance Aattributes",ReplicatedUsing= OnRep_PhysicalResistance)
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,PhysicalResistance);

	/*
	 * Meta Attributes 
	 */

	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,IncomingDamage);

	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet,IncomingXP);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence (const FGameplayAttributeData& OldIntelligence ) const;
	UFUNCTION()
	void OnRep_Resilience (const FGameplayAttributeData& OldIResilience ) const;
	UFUNCTION()
	void OnRep_Vigor (const FGameplayAttributeData& OldVigor ) const;

	UFUNCTION()
	void OnRep_Armor (const FGameplayAttributeData& OldArmor ) const;
	
	UFUNCTION()
	void OnRep_ArmorPenetration (const FGameplayAttributeData& OldArmorPenetration ) const;

	UFUNCTION()
	void OnRep_BlockChance (const FGameplayAttributeData& OldBlockChance ) const;

	UFUNCTION()
	void OnRep_CriticalHitChance (const FGameplayAttributeData& OldCriticalHitChance ) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage (const FGameplayAttributeData& OldCriticalHitDamage ) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance (const FGameplayAttributeData& OldCriticalHitResistance ) const;

	UFUNCTION()
	void OnRep_HealthRegeneration (const FGameplayAttributeData& OldHealthRegeneration ) const;

	UFUNCTION()
	void OnRep_ManaRegeneration (const FGameplayAttributeData& OldManaRegeneration ) const;

	UFUNCTION()
	void OnRep_FireResistance (const FGameplayAttributeData& OldFireResistance ) const;

	UFUNCTION()
	void OnRep_LightningResistance (const FGameplayAttributeData& OldLightningResistance ) const;

	UFUNCTION()
	void OnRep_ArcaneResistance (const FGameplayAttributeData& OldArcaneResistance ) const;

	UFUNCTION()
	void OnRep_PhysicalResistance (const FGameplayAttributeData& OldPhysicalResistance ) const;
private:

	void HandleIncomingDamage(const FEffectProperties& Props);
	void HandleIncomingXP(const FEffectProperties& Props);

	void Debuff(const FEffectProperties& Props);
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Properties) const ;

	void ShowFloatingText(const FEffectProperties& Props,float Damage,bool bBlockedHit,bool bCriticalHit)const;

	void SendXPEvent(const FEffectProperties& Props);

	bool bTopOffHealth=false;
	bool bTopOffMana=false;
	
};
