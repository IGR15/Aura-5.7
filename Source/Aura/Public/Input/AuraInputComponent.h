// IGR1S

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass,typename PressFuncType,typename ReleasedFuncType,typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,PressFuncType PressFunc,ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc);
	
	
};

template <class UserClass, typename PressFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
	PressFuncType PressFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	
	check(InputConfig);
	/**
	 * here were are going to loop all of the array of CustominputAction (array of struct) we created and then bind the press,realeased,held functions to it
	 * we are doing this cus we have the ability to pass on a gameplay tag that means we can pass these on the ability system component
	 */
	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressFunc,Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}


			
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
		}
	}
}
