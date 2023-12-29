#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API AMainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
