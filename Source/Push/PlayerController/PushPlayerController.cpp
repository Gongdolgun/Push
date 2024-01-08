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
		MainHUD->CheckWidget("KillDeathWidget");
		MainHUD->CheckWidget("StoreUIWidget");
		MainHUD->GetWidget<UKillDeathUI>("KillDeathWidget")->SetVisibility(ESlateVisibility::Hidden);
		MainHUD->GetWidget<UStoreUI>("StoreUIWidget")->SetVisibility(ESlateVisibility::Hidden);
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
		if(IsValid(resourceComponent))
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
		if(false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			CLog::Print("WaitingToStart!!");
			MainHUD->CheckWidget("StoreUIWidget");
			MainHUD->CheckWidget("ResourceWidget");
			MainHUD->GetWidget<UStoreUI>("StoreUIWidget")->SetVisibility(ESlateVisibility::Visible);
			MainHUD->GetWidget<UResource>("ResourceWidget")->SetVisibility(ESlateVisibility::Hidden);		
		}
	}
	else if (MatchState == MatchState::InProgress) // 경기
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			CLog::Print("InProgress!!");
			MainHUD->CheckWidget("StoreUIWidget");
			MainHUD->CheckWidget("ResourceWidget");
			MainHUD->GetWidget<UStoreUI>("StoreUIWidget")->SetVisibility(ESlateVisibility::Hidden);
			MainHUD->GetWidget<UResource>("ResourceWidget")->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			CLog::Print("Result!!");
			MainHUD->CheckWidget("StoreUIWidget");
			MainHUD->CheckWidget("ResourceWidget");
			MainHUD->GetWidget<UStoreUI>("StoreUIWidget")->SetVisibility(ESlateVisibility::Hidden);
			MainHUD->GetWidget<UResource>("ResourceWidget")->SetVisibility(ESlateVisibility::Hidden);
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
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;

	if(IsValid(MainHUD) && IsValid(MainHUD->GetWidget<UResource>("ResourceWidget")) && IsValid(MainHUD->GetWidget<UResource>("ResourceWidget")->HealthBar))
	{
		const float HealthPercent = Health / MaxHealth;
		MainHUD->GetWidget<UResource>("ResourceWidget")->HealthBar->SetPercent(HealthPercent);
	}
	else // HUD가 없다면
	{
		HUDHealth = Health;
		HUDMaxHealth = MaxHealth;
	}
}

void APushPlayerController::SetHUDTime() // 화면에 시간 띄우기
{
	if (MainHUD == nullptr) return;
	if (MainHUD->GetWidget<UResource>("ResourceWidget") == nullptr) return;

	float TimeLeft = 0.0f;
	if (MatchState == MatchState::WaitingToStart) // 대기
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
	else if (MatchState == MatchState::InProgress) // 경기
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime;
	else if (MatchState == MatchState::Result) // 결과
		TimeLeft = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + ResultTime;

	uint32 CountdownTime = FMath::CeilToInt(TimeLeft);

	if (MainHUD->GetWidget<UResource>("ResourceWidget")->MatchCountdownText)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		MainHUD->GetWidget<UResource>("ResourceWidget")->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}

	if (MainHUD->GetWidget<UResource>("ResourceWidget")->MatchStateTypeText)
	{
		MainHUD->GetWidget<UResource>("ResourceWidget")->MatchStateTypeText->SetText(FText::FromName(MatchState));
	}
}

void APushPlayerController::OnRep_MatchState()
{
	
}
