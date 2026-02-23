// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageAbility.h"
#include "AuraFireBlast.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBlast : public UAuraDamageAbility
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 NumFireBalls=12;
};
