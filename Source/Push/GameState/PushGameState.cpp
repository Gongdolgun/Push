#include "Push/GameState/PushGameState.h"

#include "Components/ResourceComponent.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/PushPlayerController.h"
#include "Utilites/Helpers.h"

APushGameState::APushGameState()
{
	WarmupTime = 0.f;
	MatchTime = 0.f;
	ResultTime = 0.f;
	LevelStartingTime = 0.f;
}

void APushGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APushGameState, WarmupTime);
	DOREPLIFETIME(APushGameState, MatchTime);
	DOREPLIFETIME(APushGameState, ResultTime);
	DOREPLIFETIME(APushGameState, LevelStartingTime);
	DOREPLIFETIME(APushGameState, RoundRank);
}

void APushGameState::SetTime(float wTime, float mTime, float rTime, float lTime)
{
	WarmupTime = wTime;
	MatchTime = mTime;
	ResultTime = rTime;
	LevelStartingTime = lTime;
}

void APushGameState::OnRep_TimeChanged()
{
	
}

void APushGameState::GiveGold(TArray<int32> InGoldAmount)
{
	for(uint8 i = 0; i < RoundRank.Num(); i++)
	{
		APushPlayerController* controller = RoundRank.Pop();
		UResourceComponent* resource =  Helpers::GetComponent<UResourceComponent>(controller->GetCharacter());
		resource->AdjustGold_NMC(InGoldAmount[i]);
	}
}

void APushGameState::AddToRank_Server_Implementation(APushPlayerController* InController)
{
	RoundRank.Push(InController);
}
