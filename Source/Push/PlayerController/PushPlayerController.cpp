#include "Push/PlayerController/PushPlayerController.h"
#include "HUD/MainHUD.h"
#include "GameMode/PushGameMode.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "HUD/Resource.h"
#include "Net/UnrealNetwork.h"
#include "Components/ProgressBar.h"
#include "Components/ResourceComponent.h"
#include "Components/TextBlock.h"

void APushPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainHUD = Cast<AMainHUD>(GetHUD());

	if (IsValid(MainHUD))
	{
		MainHUD->AddResourceWidget();
	}

	ServerCheckMatchState();
}

void APushPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetHUDHealth(HUDHealth, HUDMaxHealth); // WDG에서 관리할거면 삭제
	SetHUDTime(); // 시간 
}

void APushPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	TWeakObjectPtr<APushCharacter> PushCharacter = Cast<APushCharacter>(InPawn);
	UResourceComponent* resource = Helpers::GetComponent<UResourceComponent>(PushCharacter.Get());
	if (PushCharacter.IsValid())
	{
		if(IsValid(resource))
			SetHUDHealth(resource->GetHP(), resource->GetMaxHP());
	}
}

void APushPlayerController::ServerCheckMatchState_Implementation()
{
	TWeakObjectPtr<APushGameMode> GameMode = Cast<APushGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode.IsValid())
	{
		// PushGameMode.h의 값을 가져다가 넣어준다.
		MatchState = GameMode->GetMatchState();
		WarmupTime = GameMode->WarmupTime;
		MatchTime = GameMode->MatchTime;
		ResultTime = GameMode->ResultTime;
		LevelStartingTime = GameMode->LevelStartingTime;
		ClientJoinMidgame(MatchState, WarmupTime, MatchTime, ResultTime, LevelStartingTime);
	}
}

void APushPlayerController::ClientJoinMidgame_Implementation(FName StateOfMatch, float Warmup, float Match, float Result, float StartingTime)
{
	WarmupTime = Warmup;
	MatchTime = Match;
	ResultTime = Result;
	LevelStartingTime = StartingTime;
	MatchState = StateOfMatch;
	OnMatchStateSet(MatchState);
}

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

void APushPlayerController::SetHUDHealth(float Health, float MaxHealth) // WDG에서 관리할거면 삭제
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;

	if(IsValid(MainHUD) && IsValid(MainHUD->ResourceWidget) && IsValid(MainHUD->ResourceWidget->HealthBar))
	{
		const float HealthPercent = Health / MaxHealth;
		MainHUD->ResourceWidget->HealthBar->SetPercent(HealthPercent);
	}
	else // HUD가 없다면
	{
		HUDHealth = Health;
		HUDMaxHealth = MaxHealth;
	}
}

void APushPlayerController::SetHUDTime()
{
	float TimeLeft = 0.0f;
	if (MatchState == MatchState::WaitingToStart) // 대기
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
	else if (MatchState == MatchState::InProgress) // 경기
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime;
	else if (MatchState == MatchState::Result) // 결과
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + ResultTime;

	uint32 CountdownTime = FMath::CeilToInt(TimeLeft);

	if (MainHUD == nullptr)
		return;

	if (MainHUD->ResourceWidget == nullptr)
		return;

	if (MainHUD->ResourceWidget->MatchCountdownText != nullptr)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		MainHUD->ResourceWidget->MatchCountdownText->SetText(FText::FromString(CountdownText));
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
