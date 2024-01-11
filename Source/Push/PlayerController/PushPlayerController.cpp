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
#include "Widgets/KillDeathUI.h"
#include "Widgets/StoreUI.h"

void APushPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainHUD = Cast<AMainHUD>(GetHUD());

	if (IsValid(MainHUD))
	{
		MainHUD->AddWidget();
		if (MainHUD->CheckWidget("KDA"))
			MainHUD->GetWidget<UKillDeathUI>("KDA")->SetVisibility(ESlateVisibility::Hidden);

		if (MainHUD->CheckWidget("Store"))
			MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);
	}

	ClientCheckMatchState();
}

void APushPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetHUDHealth(HUDHealth, HUDMaxHealth); // WDG에서 관리할거면 삭제
	SetHUDTime(); // 시간
	//Init();
}

void APushPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TWeakObjectPtr<APushCharacter> PushCharacter = Cast<APushCharacter>(InPawn);
	resourceComponent = Helpers::GetComponent<UResourceComponent>(PushCharacter.Get());
	if (PushCharacter.IsValid())
	{
		if (IsValid(resourceComponent))
			SetHUDHealth(resourceComponent->GetHP(), resourceComponent->GetMaxHP());
	}
}

void APushPlayerController::ClientCheckMatchState_Implementation()
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
	}
}

void APushPlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;  // GameMode에서 건내받는 FName State으로 MatchState 설정

	if (MatchState == MatchState::WaitingToStart) // 대기
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			CLog::Print("WaitingToStart!!");
			if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Visible);

			if(MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);
			
		}
	}
	else if (MatchState == MatchState::InProgress) // 경기
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			CLog::Print("InProgress!!");
			if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if(MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			CLog::Print("Result!!");
			if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);;
		}
	}
}

void APushPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APushPlayerController, MatchState); // replicated 되도록 MatchState 등록
}

void APushPlayerController::Init()
{
	//if (IsValid(resourceComponent))
	//	SetHUDHealth(resourceComponent->GetMaxHP(), resourceComponent->GetMaxHP());
}

void APushPlayerController::SetHUDHealth(float Health, float MaxHealth) // WDG에서 관리할거면 삭제
{
	//MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;

	//if (IsValid(MainHUD) && IsValid(MainHUD->GetWidget<UResource>("Resource")) && IsValid(MainHUD->GetWidget<UResource>("Resource")->HealthBar))
	//{
	//	const float HealthPercent = Health / MaxHealth;
	//	MainHUD->GetWidget<UResource>("Resource")->HealthBar->SetPercent(HealthPercent);
	//}
	//else // HUD가 없다면
	//{
	//	HUDHealth = Health;
	//	HUDMaxHealth = MaxHealth;
	//}
}

void APushPlayerController::SetHUDTime() // 화면에 시간 띄우기
{
	if (MainHUD == nullptr) return;
	if (MainHUD->GetWidget<UResource>("Resource") == nullptr) return;

	float TimeLeft = 0.0f;
	if (MatchState == MatchState::WaitingToStart) // 대기
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
	else if (MatchState == MatchState::InProgress) // 경기
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime;
	else if (MatchState == MatchState::Result) // 결과
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + ResultTime;

	uint32 CountdownTime = FMath::CeilToInt(TimeLeft);

	if (MainHUD->GetWidget<UResource>("Resource")->MatchCountdownText)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		MainHUD->GetWidget<UResource>("Resource")->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}

	if (MainHUD->GetWidget<UResource>("Resource")->MatchStateTypeText)
	{
		MainHUD->GetWidget<UResource>("Resource")->MatchStateTypeText->SetText(FText::FromName(MatchState));
	}
}

void APushPlayerController::OnRep_MatchState()
{

}