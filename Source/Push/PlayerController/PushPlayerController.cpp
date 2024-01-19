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

	DOREPLIFETIME(APushPlayerController, MatchState); // replicated �ǵ��� MatchState ���
	DOREPLIFETIME(APushPlayerController, Gold); // replicated �ǵ��� MatchState ���
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

	SetHUDHealth(HUDHealth, HUDMaxHealth); // WDG���� �����ҰŸ� ����
	SetHUDTime(); // �ð�
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
		// PushGameState.h�� ���� �����ٰ� �־��ش�.
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
	MatchState = State;  // GameMode���� �ǳ��޴� FName State���� MatchState ����

	if (MatchState == MatchState::InProgress) // ���
	{
		if (false == HasAuthority())
		{
			// TODO: HUD�� ������Ʈ �Լ�
			//CLog::Print("WaitingToStart!!");
			/*if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Visible);

			if(MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);*/

		}
	}
	else if (MatchState == MatchState::Round) // ���
	{
		if (false == HasAuthority())
		{
			// TODO: HUD�� ������Ʈ �Լ�
			//CLog::Print("InProgress!!");
			/*if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if(MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Visible);*/
		}
	}
	else if (MatchState == MatchState::Result) // �����ǥ
	{
		if (false == HasAuthority())
		{
			// TODO: HUD�� ������Ʈ �Լ�
			//CLog::Print("Result!!");
			/*if(MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);;*/
		}
	}
}

void APushPlayerController::SetHUDHealth(float Health, float MaxHealth) // WDG���� �����ҰŸ� ����
{
	//MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;

	//if (IsValid(MainHUD) && IsValid(MainHUD->GetWidget<UResource>("Resource")) && IsValid(MainHUD->GetWidget<UResource>("Resource")->HealthBar))
	//{
	//	const float HealthPercent = Health / MaxHealth;
	//	MainHUD->GetWidget<UResource>("Resource")->HealthBar->SetPercent(HealthPercent);
	//}
	//else // HUD�� ���ٸ�
	//{
	//	HUDHealth = Health;
	//	HUDMaxHealth = MaxHealth;
	//}
}

void APushPlayerController::SetHUDTime() // ȭ�鿡 �ð� ����
{
	if (MainHUD == nullptr) return;
	if (MainHUD->GetWidget<UResource>("Resource") == nullptr) return;

	float TimeLeft = 0.0f;
	if (MatchState == MatchState::InProgress) // ���
	{
		TimeLeft = WarmupTime + LevelStartingTime + tempTime - GetWorld()->GetTimeSeconds();
	}
	else if (MatchState == MatchState::Round) // ���
	{
		TimeLeft = WarmupTime + LevelStartingTime + MatchTime + tempTime - GetWorld()->GetTimeSeconds();
	}
	else if (MatchState == MatchState::Result) // ���
	{
		TimeLeft = WarmupTime + LevelStartingTime + MatchTime + ResultTime + tempTime - GetWorld()->GetTimeSeconds();
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

void APushPlayerController::UpdatePlayerList_Client_Implementation(const TArray<FPlayerList>& PlayerList)
{
	if (MainHUD == nullptr) return;
	if (MainHUD->GetWidget<UKillDeathUI>("LeaderBoard") == nullptr) return;

	// Log�� ������ �÷��̾� ����ũž �̸� ���. �α׿� �� ������.
	//for (const FPlayerList& playerList : PlayerList)
	//{
	//	FString playerName = playerList.PlayerName;
	//
	//	FString message = FString::Printf(TEXT("PlayerName : %s"), *playerName);
	//	CLog::Log(message);
	//}

	if (MainHUD->GetWidget<UKillDeathUI>(TEXT("LeaderBoard")))
	{
		MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->UpdatePlayerList(PlayerList);
	}

	// ������ 0.1�� �ڿ� �ٽ� ȣ��
	else
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PlayerList]()
			{
				if (MainHUD->GetWidget<UKillDeathUI>(TEXT("LeaderBoard")))
				{
					MainHUD->GetWidget<UKillDeathUI>(TEXT("LeaderBoard"))->UpdatePlayerList(PlayerList);
				}
			}, 0.1f, false);
	}


}

void APushPlayerController::OnRep_MatchState()
{
	if (MatchState == MatchState::InProgress)
	{
		tempTime = GetWorld()->GetTimeSeconds();
	}

	if (MatchState == MatchState::InProgress) // ���
	{
		if (false == HasAuthority())
		{
			// TODO: HUD�� ������Ʈ �Լ�
			//CLog::Print("WaitingToStart!!");
			/*if (MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Visible);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);*/

		}
	}
	else if (MatchState == MatchState::Round) // ���
	{
		if (false == HasAuthority())
		{
			// TODO: HUD�� ������Ʈ �Լ�
			//CLog::Print("InProgress!!");
			/*if (MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Visible);*/
		}
	}
	else if (MatchState == MatchState::Result) // �����ǥ
	{
		if (false == HasAuthority())
		{
			// TODO: HUD�� ������Ʈ �Լ�
			//CLog::Print("Result!!");
			/*if (MainHUD->CheckWidget("Store"))
				MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);

			if (MainHUD->CheckWidget("Resource"))
				MainHUD->GetWidget<UResource>("Resource")->SetVisibility(ESlateVisibility::Hidden);*/
		}
	}
}
