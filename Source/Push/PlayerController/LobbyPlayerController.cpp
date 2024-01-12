#include "PlayerController/LobbyPlayerController.h"
#include "Global.h"
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
	
	GameState = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this));

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void ALobbyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//SetHUDCountdownTime(); // LobbyHUD의 함수 UpdateWidget()으로 '입장한 플레이어 & 시간' 업데이트 
}

void ALobbyPlayerController::SetHUDCountdownTime()
{
	if (LobbyHUD == nullptr) return;
	if (LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown") == nullptr) return;

	float TimeLeft = countdownTimer - GetWorld()->GetTimeSeconds() + LevelStartingTime;
	LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->UpdateWidget(GameState->MatchStartCountdown);

}