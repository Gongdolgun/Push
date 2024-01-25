#include "Push/GameState/PushGameState.h"
#include "Net/UnrealNetwork.h"

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
