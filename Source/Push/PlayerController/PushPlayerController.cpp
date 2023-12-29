#include "Push/PlayerController/PushPlayerController.h"
#include "HUD/MainHUD.h"
#include "GameMode/PushGameMode.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "HUD/Resource.h"
#include "Net/UnrealNetwork.h"
#include "Components/ProgressBar.h"

void APushPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainHUD = Cast<AMainHUD>(GetHUD());

	if (IsValid(MainHUD))
	{
		MainHUD->AddResourceWidget();
	}

	//ServerCheckMatchState();
}

void APushPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetHUDHealth(HUDHealth, HUDMaxHealth);
}

void APushPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TWeakObjectPtr<APushCharacter> PushCharacter = Cast<APushCharacter>(InPawn);
	if (PushCharacter.IsValid())
	{
		//SetHUDHealth(PushCharacter->GetHP(), PushCharacter->GetMaxHP());
	}
}

//void APushPlayerController::ServerCheckMatchState_Implementation()
//{
//	TWeakObjectPtr<APushGameMode> GameMode = Cast<APushGameMode>(UGameplayStatics::GetGameMode(this));
//	if (GameMode.IsValid())
//	{
//		// PushGameMode.h의 값을 가져다가 넣어준다.
//		MatchState = GameMode->GetMatchState();
//		WarmupTime = GameMode->WarmupTime;
//		MatchTime = GameMode->MatchTime;
//		ResultTime = GameMode->ResultTime;
//		LevelStartingTime = GameMode->LevelStartingTime;
//		ClientJoinMidgame(MatchState, WarmupTime, MatchTime, ResultTime, LevelStartingTime);
//	}
//}
//
//void APushPlayerController::ClientJoinMidgame_Implementation(FName StateOfMatch, float Warmup, float Match, float Result, float StartingTime)
//{
//	WarmupTime = Warmup;
//	MatchTime = Match;
//	ResultTime = Result;
//	LevelStartingTime = StartingTime;
//	MatchState = StateOfMatch;
//	OnMatchStateSet(MatchState);
//}

void APushPlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;  // GameMode에서 건내받는 FName State으로 MatchState 설정

	if (MatchState == MatchState::InProgress) // 경기
	{
		// TODO: HUD를 업데이트 함수
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		// TODO: HUD를 업데이트 함수
	}
}

void APushPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APushPlayerController, MatchState); // replicated 되도록 MatchState 등록
}

void APushPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;

	if(IsValid(MainHUD))
	{
		const float HealthPercent = Health / MaxHealth;
		MainHUD->ResourceWidget->HealthBar->SetPercent(HealthPercent);
	}
}

void APushPlayerController::OnRep_MatchState()
{
	if (MatchState == MatchState::InProgress) // 경기
	{
		// TODO: HUD를 업데이트 함수
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		// TODO: HUD를 업데이트 함수
	}
}
