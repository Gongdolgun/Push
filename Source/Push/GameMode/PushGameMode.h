#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PushGameMode.generated.h"

UCLASS(minimalapi)
class APushGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APushGameMode();

protected:
	virtual void BeginPlay() override;

};