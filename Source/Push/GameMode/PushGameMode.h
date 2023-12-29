#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PushGameMode.generated.h"

UCLASS(minimalapi)
class APushGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APushGameMode();

protected:
	virtual void BeginPlay() override;

};