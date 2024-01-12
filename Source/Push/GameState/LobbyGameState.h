#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

UCLASS()
class PUSH_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()

public:



private:
	uint8 NumOfPlayers = 0;
};
