#include "PlayerController/LobbyPlayerController.h"
#include "Global.h"
#include "GameMode/LobbyGameMode.h"
#include "GameState/LobbyGameState.h"
#include "HUD/LobbyHUD.h"
#include "Widgets/LobbyCountDown.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	LobbyHUD = Cast<ALobbyHUD>(GetHUD());

	if (IsValid(LobbyHUD))
	{
		LobbyHUD->AddWidget();
		if(LobbyHUD->CheckWidget("LobbyCountDown"))
			LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->SetVisibility(ESlateVisibility::Visible);
	}

	//GameMode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
	//if (GameMode == nullptr) CLog::Log("Fail to bring GameMode World time.");

	//if(IsValid(GameMode))
	//{
	//	LevelStartingTime = GameMode->GetWorld()->GetTimeSeconds();
	//	CLog::Print("Success to bring GameMode World time.");
	//	CLog::Log("Success to bring GameMode World time.");
	//	CLog::Print(LevelStartingTime);
	//	CLog::Log(LevelStartingTime);
	//}

	GameState = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this));
	if(GameState == nullptr) CLog::Log("Fail to bring GameState.");

	if(IsValid(GameState))
	{
		//LevelStartingTime = GameState->CurrentServerTime;
		//CLog::Print("Success to bring GameState time.");
		//CLog::Log("Success to bring GameState time.");
		//CLog::Print(LevelStartingTime);
		//CLog::Log(LevelStartingTime);
		CLog::Log(ServerTime);
	}
}

void ALobbyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetHUDCountdownTime();
	/*if(IsValid(GameMode))
	{
		SetHUDCountdownTime(GameMode->countdownTimer);		
	}*/
}

void ALobbyPlayerController::SetHUDCountdownTime()
{
	if (LobbyHUD == nullptr) return;
	if (LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown") == nullptr) return;

	float TimeLeft = countdownTimer - GetWorld()->GetTimeSeconds() + ServerTime;
	LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->UpdateCountdown(TimeLeft);
}

void ALobbyPlayerController::Client_ReceiveCurrentTimeFromServer_Implementation(float CurrentTime)
{
	ServerTime = CurrentTime;
	float TimeDifference = CurrentTime - ServerTime;
}

//void ALobbyPlayerController::SetHUDCountdownTime(float InTime)
//{
//	if (LobbyHUD == nullptr) return;
//	if (LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown") == nullptr) return;
//
//	LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->UpdateCountdown(InTime);
//}
//
//void ALobbyPlayerController::ClientCheck_Implementation()
//{
//	if (GameMode == nullptr) return;
//
//	if (IsValid(GameMode))
//	{
//		countdownTimer = GameMode->countdownTimer;
//		LevelStartingTime = GameMode->LevelStartingTime;
//	}
//}
