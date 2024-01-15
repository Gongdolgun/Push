#include "PushGameMode.h"
#include "Character/PushCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerController/PushPlayerController.h"
#include "GameInstance/PushGameInstance.h"
#include "Utilites/CLog.h"
#include "Widgets/StoreUI.h"

namespace MatchState
{
	const FName Result = FName("Result"); // 결과발표. 내장되지 않은 MatchState을 사용시 명시해서 사용
}

APushGameMode::APushGameMode()
{
	bDelayedStart = true; // true면 GameMode가 start 되기 전에 waiting 상태. false면 MatchState::WaitingToStart는 비활성화되어 실행되지 않는다

}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
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
	//for(APushPlayerController* control : Controllers)
	//{
	//	control->ChangeBodyColor_Client_Implementation();
	//}

	APushCharacter* character = Cast<APushCharacter>(controller->GetPawn());

	if (character == nullptr)
	{
		CLog::Log("No Character");
		return;
	}

	character->BodyColor = Colors[index++];
}
