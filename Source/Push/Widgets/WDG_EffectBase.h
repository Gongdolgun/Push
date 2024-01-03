#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WDG_EffectBase.generated.h"

UCLASS(Abstract)
class PUSH_API UWDG_EffectBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void PlayEffect();
};
