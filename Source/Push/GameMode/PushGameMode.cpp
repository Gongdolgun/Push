#include "PushGameMode.h"
#include "Character/PushCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerController/PushPlayerController.h"
#include "GameInstance/PushGameInstance.h"
#include "GameState/PushGameState.h"
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
	bDelayedStart = false;
	
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
	if (MatchState == MatchState::WaitingToStart) // 대기
	{
		// 대기시간 - 현재시간 + 게임레벨맵에 들어간 시간
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + tempTime;
		if (CountdownTime <= 0.0f) // 대기시간이 끝나면 경기시작
		{
			SetMatchState(MatchState::InProgress);
		}
	}
	else if (MatchState == MatchState::InProgress) // 경기
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
			SetMatchState(MatchState::WaitingToStart);
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

	character->BodyColor = Colors[index++];
}
