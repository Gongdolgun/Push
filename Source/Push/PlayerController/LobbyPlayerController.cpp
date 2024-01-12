#include "PlayerController/LobbyPlayerController.h"
#include "Global.h"
#include "GameMode/LobbyGameMode.h"
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

	GameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(this));

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void ALobbyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetHUDCountdownTime();
}

void ALobbyPlayerController::SetHUDCountdownTime()
{
	if (LobbyHUD == nullptr) return;
	if (LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown") == nullptr) return;

	float TimeLeft = countdownTimer - GetWorld()->GetTimeSeconds() + LevelStartingTime;
	LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->UpdateCountdown(TimeLeft);
	
}

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
