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
#include "Widgets/StoreUI.h"

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

	LevelStartingTime = GetWorld()->GetTimeSeconds();

	APushGameState* pushGameState = Cast<APushGameState>(GameState);

	if(pushGameState == nullptr){ // ����ó��
		CLog::Log("pushGameState == nullptr !!");
		return;
	}

	// GameState�� �ð�����ȭ
	if (IsValid(pushGameState))
	{
		pushGameState->SetTime(WarmupTime, MatchTime, ResultTime, LevelStartingTime);
	}
}

void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//** '���ð� > ���ð� > ����ð�'�� �ݺ�
	if (MatchState == MatchState::InProgress) // ���
	{
		// ���ð� - ����ð� + ���ӷ����ʿ� �� �ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + tempTime;
		if (CountdownTime <= 0.0f) // ���ð��� ������ ������
		{
			SetMatchState(MatchState::Round);
		}
	}
	else if (MatchState == MatchState::Round) // ���
	{
		// ���ð� - ����ð� + ���ӷ����ʿ� �� �ð� + ������ ���ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + tempTime;
		if (CountdownTime <= 0.0f)
		{
			SetMatchState(MatchState::Result); // �����ǥ
		}
	}
	else if (MatchState == MatchState::Result) // �����ǥ
	{
		// ���ð� - ���� �ð� + ���ӷ����ʿ� �� �ð� + ������ ���ð� + ������ �����ǥ�ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + ResultTime + tempTime;
		if (CountdownTime <= 0.0f) 
		{
			tempTime = GetWorld()->GetTimeSeconds();
			SetMatchState(MatchState::InProgress);
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
					PlayerData.PlayerName = pushCharacter->CustomPlayerName;
					PlayerData.Gold = pushController->Gold;

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




