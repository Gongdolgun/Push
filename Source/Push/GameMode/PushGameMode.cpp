#include "PushGameMode.h"
#include "Push/Character/PushCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerController/PushPlayerController.h"

namespace MatchState
{
	const FName Result = FName("Result");
}

APushGameMode::APushGameMode()
{
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP///Character/BP_PushCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	bDelayedStart = true; // true면 GameMode가 start 되기 전에 waiting 상태
}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MatchState == MatchState::WaitingToStart) // 대기
	{
		// 대기시간 - 현재시간 + 게임레벨맵에 들어간 시간
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.0f) // 대기시간이 끝나면 경기시작
		{
			StartMatch(); // 경기
		}
	}
	else if (MatchState == MatchState::InProgress) // 경기
	{
		// 대기시간 - 현재시간 + 게임레벨맵에 들어간 시간 + 설정한 경기시간
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime;
		if (CountdownTime <= 0.0f)
		{
			SetMatchState(MatchState::Result); // 결과발표
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		// 대기시간 - 현재 시간 + 게임레벨맵에 들어간 시간 + 설정한 경기시간 + 설정한 결과발표시간
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + ResultTime;
		if (CountdownTime <= 0.0f) 
		{
			RestartGame(); // 경기 재시작. GameMode 내장 클래스에 정의된 함수 콜
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
