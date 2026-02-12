// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;
/**/
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();
	virtual void PossessedBy(AController* NewController) override;

	//Enemy Interface
	
	virtual void HighLightActor() override;
	virtual void UnHighLightAcotr() override;

	/**CombatInterface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/** EndCombatIterface*/
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallBackTag,int32 NewCount);

	UPROPERTY(BlueprintReadOnly,Category="combat")
	bool bHitReacting=false;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="combat")
	float LifeSpan=5.f;

	UPROPERTY(BlueprintReadWrite,Category="Combat")
	TObjectPtr<AActor>CombatTarget;
	
protected:
	
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfor()override;
	
	virtual void InitializeDefaultAttributes()const override;


	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="charcter class defaults")
	int32 level=1;

		
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent>HealthBar;

	UPROPERTY(EditAnywhere,Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
	
};
