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
	const FName Result = FName("Result"); // 결과발표. 내장되지 않은 MatchState을 사용시 명시해서 사용
}

APushGameMode::APushGameMode()
{
	bDelayedStart = true; // 캐릭터가 시작부터 끝까지 계속 스폰되어 있어야하므로 MatchState::WaitingToStart를 없애고 bDelayedStart = true로 변경하였다.
	
}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();

	APushGameState* pushGameState = Cast<APushGameState>(GameState);

	if(pushGameState == nullptr){ // 예외처리
		CLog::Log("pushGameState == nullptr !!");
		return;
	}

	// GameState에 시간동기화
	if (IsValid(pushGameState))
	{
		pushGameState->SetTime(WarmupTime, MatchTime, ResultTime, LevelStartingTime);
	}
}

void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//** '대기시간 > 경기시간 > 결과시간'을 반복
	if (MatchState == MatchState::InProgress) // 대기
	{
		// 대기시간 - 현재시간 + 게임레벨맵에 들어간 시간
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + tempTime;
		if (CountdownTime <= 0.0f) // 대기시간이 끝나면 경기시작
		{
			SetMatchState(MatchState::Round);
		}
	}
	else if (MatchState == MatchState::Round) // 경기
	{
		// 대기시간 - 현재시간 + 게임레벨맵에 들어간 시간 + 설정한 경기시간
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + tempTime;
		if (CountdownTime <= 0.0f)
		{
			SetMatchState(MatchState::Result); // 결과발표
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		// 대기시간 - 현재 시간 + 게임레벨맵에 들어간 시간 + 설정한 경기시간 + 설정한 결과발표시간
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

	// GameMode의 MatchState이 변경되면 서버에서 해당되는 PlayerController를 찾아 MatchState을 설정한다.
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
	PlayerListData.Empty();

	for (APlayerController* playerContrller : AllPC)
	{
		if (playerContrller)
		{
			FString PlayerName = playerContrller->PlayerState->GetPlayerName();

			FPlayerList NewPlayer;
			NewPlayer.PlayerName = PlayerName;
			
			PlayerListData.Add(NewPlayer);
		}
	}

	for (APlayerController* playerController : AllPC)
	{
		APushPlayerController* pushPlayerController = Cast<APushPlayerController>(playerController);
		if (pushPlayerController)
			pushPlayerController->UpdatePlayerList_Client(PlayerListData);
	}
}




