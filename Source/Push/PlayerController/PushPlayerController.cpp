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
#include "Widgets/LeaderBoard_List.h"
#include "Widgets/StoreUI.h"

void APushPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APushPlayerController, MatchState); // replicated 되도록 MatchState 등록
	DOREPLIFETIME(APushPlayerController, Gold);
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

		if (MainHUD->CheckWidget("LeaderBoard_List"))
			MainHUD->GetWidget<ULeaderBoard_List>("LeaderBoard_List")->SetVisibility(ESlateVisibility::Hidden);

		if (MainHUD->CheckWidget("Store"))
			MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);
	}

	ClientCheckMatchState();
}

void APushPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetHUDTime(); // 시간
}

void APushPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TWeakObjectPtr<APushCharacter> PushCharacter = Cast<APushCharacter>(InPawn);
	resourceComponent = Helpers::GetComponent<UResourceComponent>(PushCharacter.Get());
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

		OnMatchStateSet(MatchState);
	}
}

void APushPlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;  // GameMode에서 건내받는 FName State으로 MatchState 설정
}

void APushPlayerController::SetHUDTime() // 화면에 시간 띄우기
{
	if (MainHUD == nullptr) return;
	if (MainHUD->GetWidget<UResource>("Resource") == nullptr) return;

	float TimeLeft = 0.0f;
	if (MatchState == MatchState::InProgress) // 대기
	{
		TimeLeft = WarmupTime + LevelStartingTime + tempTime - GetWorld()->GetTimeSeconds();
	}
	else if (MatchState == MatchState::Round) // 경기
	{
		TimeLeft = WarmupTime + LevelStartingTime + MatchTime + tempTime - GetWorld()->GetTimeSeconds();
	}
	else if (MatchState == MatchState::Result) // 결과
	{
		TimeLeft = WarmupTime + LevelStartingTime + MatchTime + ResultTime + tempTime - GetWorld()->GetTimeSeconds();
	}

	uint32 CountdownTime = FMath::CeilToInt(TimeLeft);

	// 시간 띄우기
	if (MainHUD->GetWidget<UResource>("Resource")->MatchCountdownText)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		MainHUD->GetWidget<UResource>("Resource")->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
	// MatchState 띄우기
	if (MainHUD->GetWidget<UResource>("Resource")->MatchStateTypeText)
	{
		FText name;
		if (MatchState == MatchState::InProgress) name = FText::FromString("Store");
		else if (MatchState == MatchState::Round) name = FText::FromString("Round");
		else if (MatchState == MatchState::Result) name = FText::FromString("Result");

		MainHUD->GetWidget<UResource>("Resource")->MatchStateTypeText->SetText(name);
	}
}

void APushPlayerController::UpdatePlayerList_Server_Implementation(const TArray<FPlayerList>& PlayerList)
{
	UpdatePlayerList_NMC(PlayerList);
}

void APushPlayerController::UpdatePlayerList_NMC_Implementation(const TArray<FPlayerList>& PlayerList)
{
	if (MainHUD == nullptr) return;
	//if (MainHUD->GetWidget<UKillDeathUI>("LeaderBoard") == nullptr) return;

	// 정상적으로 호출이 되었으면, PlayerList Update
	if (MainHUD->GetWidget<UKillDeathUI>(TEXT("LeaderBoard")) == nullptr)
	{
		MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->UpdatePlayerList(PlayerList);

	}
	// 리더보드가 인식이 되지 않았으면 0.1초 뒤에 다시 호출
	else
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PlayerList]()
		{
			MainHUD->GetWidget<UKillDeathUI>(TEXT("LeaderBoard"))->UpdatePlayerList(PlayerList);
		}, 0.2f, false);
	}
}

void APushPlayerController::OnRep_MatchState()
{
	if (MatchState == MatchState::InProgress)
	{
		tempTime = GetWorld()->GetTimeSeconds();
	}

}