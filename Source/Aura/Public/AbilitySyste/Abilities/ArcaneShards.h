// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageAbility.h"
#include "ArcaneShards.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UArcaneShards : public UAuraDamageAbility
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 MaxNumberOfShards=11;
};
