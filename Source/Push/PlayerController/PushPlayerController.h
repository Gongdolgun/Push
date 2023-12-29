#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PushPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API APushPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};

