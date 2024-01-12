#include "GameState/LobbyGameState.h"
#include "Net/UnrealNetwork.h"
#include "Utilites/CLog.h"
#include "HUD/LobbyHUD.h"
#include "Widgets/LobbyCountDown.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameState, currentNumOfPlayers);
	DOREPLIFETIME(ALobbyGameState, MatchStartCountdown);
}

void ALobbyGameState::PlayerConnection()
{
	currentNumOfPlayers = PlayerArray.Num();
	CLog::Print("currentNumOfPlayers = ");
	CLog::Print(currentNumOfPlayers);
	CLog::Log("currentNumOfPlayers = ");
	CLog::Log(currentNumOfPlayers);

	if (currentNumOfPlayers >= 3)
	{
		if (MatchStartCountdown >= 20)
		{
			MatchStartCountdown = 5;
		}
	}
}

void ALobbyGameState::OnRep_MatchStartCountdown() 
{
	UpdateMatchStartCountdownWidget();

	if (MatchStartCountdown >= 5)
	{
		MatchCountDown();
	}
	else
	{
		if (MatchStartCountdown == 0) CLog::Log("Start Match!! & Move to another Game Level!");
		else MatchCountDown();
	}
}

void ALobbyGameState::MatchCountDown()
{
	GetWorld()->GetTimerManager().SetTimer(LobbyTimeHandle, this, &ALobbyGameState::CountDown, 1.0f, true, 0);

}
void ALobbyGameState::CountDown()
{
	MatchStartCountdown -= 1;

}

void ALobbyGameState::UpdateMatchStartCountdownWidget()
{
	ALobbyHUD* lobbyHUD = Cast<ALobbyHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (lobbyHUD == nullptr) return;
	if (false == lobbyHUD->CheckWidget("LobbyCountDown")) return;

	lobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->UpdateWidget(MatchStartCountdown);
}
