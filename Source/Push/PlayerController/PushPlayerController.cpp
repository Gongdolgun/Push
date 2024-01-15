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
#include "GameState/PushGameState.h"
#include "Widgets/KillDeathUI.h"
#include "Widgets/StoreUI.h"

void APushPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APushPlayerController, MatchState); // replicated 되도록 MatchState 등록
}

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
	GameState = Cast<APushGameState>(UGameplayStatics::GetGameState(this));
	if (IsValid(GameState))
	{
		// PushGameState.h의 값을 가져다가 넣어준다.
		MatchState = GameState->GetMatchState();
		WarmupTime = GameState->WarmupTime;
		MatchTime = GameState->MatchTime;
		ResultTime = GameState->ResultTime;
		LevelStartingTime = GameState->LevelStartingTime;

		CLog::Print(MatchTime);
		CLog::Print(WarmupTime);
		CLog::Print(ResultTime);
		CLog::Print(LevelStartingTime);

		OnMatchStateSet(MatchState);
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
			//CLog::Print("WaitingToStart!!");
			/*if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Visible);

			if(MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);*/
			
		}
	}
	else if (MatchState == MatchState::InProgress) // 경기
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			//CLog::Print("InProgress!!");
			/*if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if(MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Visible);*/
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			//CLog::Print("Result!!");
			/*if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);;*/
		}
	}
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
	{
		TimeLeft = WarmupTime + LevelStartingTime + tempTime - GetWorld()->GetTimeSeconds();
		//CLog::Print(WarmupTime);
	}
	else if (MatchState == MatchState::InProgress) // 경기
	{
		TimeLeft = LevelStartingTime + MatchTime + tempTime - GetWorld()->GetTimeSeconds();
		//CLog::Print(MatchTime);
	}
	else if (MatchState == MatchState::Result) // 결과
	{
		TimeLeft = LevelStartingTime + ResultTime + tempTime - GetWorld()->GetTimeSeconds();
		//CLog::Print(ResultTime);
	}
	

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
	tempTime = GetWorld()->GetTimeSeconds();

	if (MatchState == MatchState::WaitingToStart) // 대기
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			//CLog::Print("WaitingToStart!!");
			/*if (MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Visible);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);*/

		}
	}
	else if (MatchState == MatchState::InProgress) // 경기
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			//CLog::Print("InProgress!!");
			/*if (MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Visible);*/
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		if (false == HasAuthority())
		{
			// TODO: HUD를 업데이트 함수
			//CLog::Print("Result!!");
			/*if (MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);*/
		}
	}
}