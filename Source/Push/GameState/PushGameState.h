#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PushGameState.generated.h"


UCLASS()
class PUSH_API APushGameState : public AGameState
{
	GENERATED_BODY()

public:
	APushGameState();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	float CurrentServerTime;
};
