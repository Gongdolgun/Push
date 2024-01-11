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

void APushGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentServerTime = GetServerWorldTimeSeconds();
}
