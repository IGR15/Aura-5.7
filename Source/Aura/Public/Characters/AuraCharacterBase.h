// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UDebuffNiagaraComponent;
class UNiagaraSystem;
class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet()const {return AttributeSet;}
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;



	UFUNCTION(NetMulticast,Reliable)
	virtual void MultiCastHandleDeath(const FVector& DeathImpulse);//this is going to handel all the death on the clients

	/*combat interface*/
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation()  override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual USkeletalMeshComponent* GetWeapon_Implementation() override;

	FOnASCRegistered OnAscRegistered;
	virtual FOnASCRegistered GetOnASCRegisteredDelegate() override;

	FOnDeathSignature OnDeathDelegatee;
	virtual FOnDeathSignature& GetOnDeathDelegate() override;
	/* end combat interface*/

	UPROPERTY(EditAnywhere,Category="Combat")
	TArray<FTaggedMontage> AttackMontages;
	
	UPROPERTY(Replicated,BlueprintReadOnly)
	bool bIsStunned=false;
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="combat")
	float BasewalkSpeed=600.f;
	
	bool bDead = false;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="charcter class defaults")
	ECharacterClass CharacterClass=ECharacterClass::Warrior;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere,Category="Combat")
	FName WeaponTimSocketName;
	UPROPERTY(EditAnywhere,Category="Combat")
	FName LeftHandSocketName;
	UPROPERTY(EditAnywhere,Category="Combat")
	FName RightHandSocketName;
	UPROPERTY(EditAnywhere,Category="Combat")
	FName TailSocketName;

	virtual void StunTagChanged(const FGameplayTag CallbackTag,int32 NewCount);


	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfor();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttribute;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttribute;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttribute;

	

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	virtual void InitializeDefaultAttributes()const;

	void AddCharacterAbilities();

	/*Dissolve Effects*/

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>DissolveMaterialInstance;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="combat")
	UNiagaraSystem* BloodEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="combat")
	USoundBase* DeathSound;

	/*Minions*/
	
	int32 MinionCount;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent> BurnDebuffComponent;

private:
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>>StartUpAbilities;

	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>>StartUpPassiveAbilities;

	UPROPERTY(EditAnywhere,Category="combat")
	TObjectPtr<UAnimMontage>HitReactMontage;
	
};
