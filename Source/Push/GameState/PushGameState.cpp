#include "Push/GameState/PushGameState.h"

#include "Components/ResourceComponent.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/PushPlayerController.h"
#include "Utilites/Helpers.h"

APushGameState::APushGameState()
{
	CurrentTime = 0.0f;
}

void APushGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APushGameState, CurrentTime);
	DOREPLIFETIME(APushGameState, RoundRank);
}

void APushGameState::SetTime(float InTime)
{
	CurrentTime = InTime;
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
