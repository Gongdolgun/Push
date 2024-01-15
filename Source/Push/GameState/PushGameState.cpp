#include "Push/GameState/PushGameState.h"
#include "Character/PushCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Global.h"

APushGameState::APushGameState()
{

}

void APushGameState::BeginPlay()
{
	Super::BeginPlay();
	
}

void APushGameState::PlayerConnection()
{
	currentNumOfPlayers = PlayerArray.Num();
	GetGameTimeSinceCreation()

	if (currentNumOfPlayers >= 3)
	{
		
	}
}
