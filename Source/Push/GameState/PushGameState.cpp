#include "Push/GameState/PushGameState.h"
#include "Character/PushCharacter.h"
#include "Components/ResourceComponent.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/PushPlayerController.h"
#include "Utilites/Helpers.h"
#include "Widgets/Rank.h"
#include "Components/TextBlock.h"
#include "Utilites/CLog.h"

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

void APushGameState::UpdateGameNum(uint8 InNumofGames)
{
	for (APlayerState* player : PlayerArray)
	{
		APushCharacter* character = Cast<APushCharacter>(player->GetPawn());

		if (character == nullptr)
			continue;

		APushPlayerController* controller = Cast<APushPlayerController>(character->GetController());

		if (controller == nullptr)
			continue;

		controller->UpdateGameNum_Client(InNumofGames);
	}
}

void APushGameState::ShowTotalRank()
{
	TArray<APushPlayerController*> Controllers;

	CLog::Log("ShowRank");

	for (APlayerState* player : PlayerArray)
	{
		APushCharacter* character = Cast<APushCharacter>(player->GetPawn());

		if (character == nullptr)
			continue;

		APushPlayerController* controller = Cast<APushPlayerController>(character->GetController());

		if (controller == nullptr)
			continue;

		Controllers.Add(controller);
		CLog::Log("Controller Add");
	}

	Controllers.Sort([](APushPlayerController& A, APushPlayerController& B)
	{
		uint8 AKill = A.resourceComponent->GetKill();
		uint8 BKill = B.resourceComponent->GetKill();

		return AKill > BKill;
	});

	int Rank = 1;
	uint8 CurrentKill = Controllers[0]->resourceComponent->GetKill();

	if (Controllers.Num() == 0)
		CLog::Log("Controllers Empty");

	for (APushPlayerController* controller : Controllers)
	{
		uint8 thisKill = controller->resourceComponent->GetKill();

		CLog::Log(thisKill);
		if (thisKill < CurrentKill)
		{
			Rank++;
			CurrentKill = thisKill;
		}
		CLog::Log("ShowRankClient");
		CLog::Log(Rank);

		controller->ShowRank_Client(Rank, RankWidget);
	}
}

void APushGameState::GiveGold(TArray<int32> InGoldAmount, int32 InBaseMoney)
{
	CLog::Log("GiveGold");
	int num = RoundRank.Num();
	for (uint8 i = 0; i < num; i++)
	{
		APushPlayerController* controller = RoundRank.Pop();
		UResourceComponent* resource = Helpers::GetComponent<UResourceComponent>(controller->GetCharacter());

		CLog::Log(InGoldAmount[i]);
		resource->AdjustGold_NMC(InGoldAmount[i] + InBaseMoney);
	}
}

void APushGameState::AddToRank(APushPlayerController* InController)
{
	RoundRank.Push(InController);
}
