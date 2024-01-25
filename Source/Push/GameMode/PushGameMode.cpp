#include "PushGameMode.h"
#include "Character/PushCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerController/PushPlayerController.h"
#include "GameInstance/PushGameInstance.h"
#include "GameState/PushGameState.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Utilites/CLog.h"
#include "Global.h"
#include "Components/ResourceComponent.h"
#include "Widgets/StoreUI.h"
#include "Objects/Ring.h"

namespace MatchState
{
	const FName Round = FName("Round"); 
}

namespace MatchState
{
	const FName Result = FName("Result"); // �����ǥ. ������� ���� MatchState�� ���� ����ؼ� ���
}

APushGameMode::APushGameMode()
{
	bDelayedStart = true; // ĳ���Ͱ� ���ۺ��� ������ ��� �����Ǿ� �־���ϹǷ� MatchState::WaitingToStart�� ���ְ� bDelayedStart = true�� �����Ͽ���.
	
}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	tempTime = GetWorld()->GetTimeSeconds();
	CountdownTime = WarmupTime;

	PushGameState = Cast<APushGameState>(GameState);

	if(PushGameState == nullptr){ // ����ó��
		CLog::Log("pushGameState == nullptr !!");
		return;
	}

	// GameState�� �ð�����ȭ
	if (IsValid(PushGameState))
	{
		PushGameState->SetTime(WarmupTime, RoundTime[Round], ResultTime, tempTime);
	}

	TWeakObjectPtr<UWorld> world = GetWorld();

	if (world.IsValid())
	{
		if (IsValid(RingClass))
		{
			Ring = world->SpawnActor<ARing>(RingClass);
		}
	}
}

void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MatchState == MatchState::InProgress) // ����
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f)
		{
			SetMatchState(MatchState::Round);
			CountdownTime = RoundTime[Round];
			tempTime = GetWorld()->GetTimeSeconds();
		}
	}
	else if (MatchState == MatchState::Round) // ����s
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f)
		{
			if (RoundTime.Num() - 1 <= Round)
			{
				tempTime = GetWorld()->GetTimeSeconds();
				CountdownTime = ResultTime;
				Round = 0;
				SetMatchState(MatchState::Result); // �����ǥ
			}
			else
			{
				if (Ring.Get() != nullptr)
					Ring.Get()->Shrink(RingRadius[Round], 10);

				CountdownTime = RoundTime[++Round];
				tempTime = GetWorld()->GetTimeSeconds();
			}
		}
	}
	else if (MatchState == MatchState::Result) // �����ǥ
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f) 
		{
			SetMatchState(MatchState::InProgress);
			tempTime = GetWorld()->GetTimeSeconds();
			CountdownTime = WarmupTime;
		}
	}
}

void APushGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	// GameMode�� MatchState�� ����Ǹ� �������� �ش�Ǵ� PlayerController�� ã�� MatchState�� �����Ѵ�.
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		TWeakObjectPtr<APushPlayerController> SelectedPlayer = Cast<APushPlayerController>(*It);
		if (SelectedPlayer.IsValid())
		{
			SelectedPlayer->OnMatchStateSet(MatchState);
		}
	}
}

void APushGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	APushPlayerController* controller = Cast<APushPlayerController>(NewPlayer);

	if (controller == nullptr)
		return;

	APushCharacter* character = Cast<APushCharacter>(controller->GetPawn());

	if (character == nullptr)
	{
		CLog::Log("No Character");
		return;
	}

	CLog::Log("Post Login In the Game");
	

	character->BodyColor = Colors[index++];

	AllPC.Add(NewPlayer);
	UpdatePlayerList();
}

void APushGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerController* playercontroller = Cast<APlayerController>(Exiting);
	AllPC.Empty();

	UpdatePlayerList();
}

void APushGameMode::UpdatePlayerList()
{
	// �÷��̾� ����Ʈ�� ����ְ�, GameState���� Player�� �̸��� �����ͼ� ����
	PlayerListData.Empty();

	for (APlayerController* playerContrller : AllPC)
	{
		if (playerContrller)
		{
			APushPlayerController* pushController = Cast<APushPlayerController>(playerContrller);
			APawn* pawn = playerContrller->GetPawn();
			// ������Ʈ�� ����� �ȵǰ� ������ ������ ��찡 ���ܼ� 0.2�ʵڿ� �ٽ� �Լ� ����
			if (!pawn)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(
					TimerHandle, this, &APushGameMode::UpdatePlayerList, 0.2f, false);
			}

			else
			{
				// Lobby���� �Էµ� �̸��� CustomPlayerName�� ��µǵ��� ����
				APushCharacter* pushCharacter = Cast<APushCharacter>(pawn);
				if (pushCharacter)
				{
					UResourceComponent* resource = Helpers::GetComponent<UResourceComponent>(pushCharacter);

					PlayerData.PlayerName = pushCharacter->CustomPlayerName;
					PlayerData.Gold = resource->GetGold();
					PlayerData.Kill = resource->GetKill();
					PlayerData.Death = resource->GetDeath();

					PlayerListData.Add(PlayerData);
				}
			}
		}
	}

	// �÷��̾� ����Ʈ ������Ʈ
	for (APlayerController* playerController : AllPC)
	{
		APushPlayerController* pushPlayerController = Cast<APushPlayerController>(playerController);

		if (pushPlayerController)
			pushPlayerController->UpdatePlayerList_Server(PlayerListData);
	}
}

void APushGameMode::SetMatchState(FName NewState)
{
	Super::SetMatchState(NewState);

	if(NewState == MatchState::Result)
	{
		PushGameState->GiveGold(MoneyPerRank);
	}
}
