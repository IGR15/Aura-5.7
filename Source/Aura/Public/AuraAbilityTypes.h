#pragma once

#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject>WorldContextObject=nullptr;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect>DamageGameplayEffectClass=nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent>SourceASC;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent>TargetASC;
	
	UPROPERTY(BlueprintReadWrite)
	float BaseDamage=0.f;
	
	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel=1.f;
	
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag DamageType = FGameplayTag();
	
	UPROPERTY(BlueprintReadWrite)
	float DebuffChance=0.f;
	
	UPROPERTY(BlueprintReadWrite)
	float DebuffDamage=0.f;
	
	UPROPERTY(BlueprintReadWrite)
	float DebuffDuration=0.f;
	
	UPROPERTY(BlueprintReadWrite)
	float DebuffFrequency=0.f;

	UPROPERTY(BlueprintReadWrite)
	float DeathImpulseMagnitude=0.f;

	UPROPERTY(BlueprintReadWrite)
	FVector DeathImpulse=FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	float KnockbackForceMagnitude=0.f;

	UPROPERTY(BlueprintReadWrite)
	FVector KnockbackForce=FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	float KnocKbackChance=0.f;
	
};
USTRUCT(BlueprintType)
struct FAuraGamePlayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
public:
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}
	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FAuraGamePlayEffectContext* Duplicate() const
	{
		FAuraGamePlayEffectContext* NewContext = new FAuraGamePlayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	bool IsCriticalHit()const { return bIsCriticalHit;}
	bool IsBlockedHit()const { return bIsBlockedHit;}
	bool IsSuccessFullDebuff()const {return bIsSuccessfulDebuff;}
	float GetDebuffDamage()const {return DebuffDamage;}
	float GetDebuffDuration()const {return DebuffDuration;}
	float GetDebuffFrequency()const {return DebuffFrequency;}
	TSharedPtr<FGameplayTag> GetDamageType()const {return DamageType;}
	FVector GetDeathImpulse()const {return DeathImpulse;}
	FVector GetKnockbackForce()const {return KnockbackForce;}

	void SetIsCriticalHit(bool bInIsCriticalHit){bIsCriticalHit=bInIsCriticalHit;}
	void SetIsBlockedHit(bool bInIsBlockedHit){bIsBlockedHit=bInIsBlockedHit;}
	void SetIsSuccessFullDebuf(bool bInSuccessFullDebuff){bIsSuccessfulDebuff=bInSuccessFullDebuff;}
	void SetDebuffDamage(float InDamage){DebuffDamage=InDamage;}
	void SetDebuffDuration(float InDebuffDuration){DebuffDuration=InDebuffDuration;}
	void SetDebuffFrequency(float InFrequency){DebuffFrequency=InFrequency;}
	void SetDamageType(const TSharedPtr<FGameplayTag>& InDamageType){DamageType=InDamageType;}
	void SetDeathImpulse(const FVector& InImpulse){DeathImpulse=InImpulse;}
	void SetKnockbackForce(const FVector& InForce){KnockbackForce=InForce;}

	

protected:
	UPROPERTY()
	bool bIsBlockedHit=false;
	UPROPERTY()
	bool bIsCriticalHit=false;

	UPROPERTY()
	bool bIsSuccessfulDebuff=false;

	UPROPERTY()
	float DebuffDamage=0.f;

	UPROPERTY()
	float DebuffDuration=0.f;

	UPROPERTY()
	float DebuffFrequency=0.f;
	
	TSharedPtr<FGameplayTag>DamageType;

	UPROPERTY()
	FVector DeathImpulse=FVector::ZeroVector;

	UPROPERTY()
	FVector KnockbackForce=FVector::ZeroVector;
	
};
template <>
struct TStructOpsTypeTraits<FAuraGamePlayEffectContext> :  TStructOpsTypeTraitsBase2<FAuraGamePlayEffectContext>
{
	enum
	{
		WithNetSerializer=true,
		WithCopy=true
	};
};
