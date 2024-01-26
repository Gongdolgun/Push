#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameState.h"
#include "GameState/LobbyGameState.h"
#include "Utilites/CLog.h"
#include "Widgets/LobbyCountDown.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NumOfPlayers++;

	if (false == IsValid(NewPlayer)) return;

	if (HasAuthority())
	{
		TWeakObjectPtr<UGameInstance> GameInstance = GetGameInstance();
		if (GameInstance.IsValid())
		{
			if (NumOfPlayers >= MaxNumofPlayers)
			{
				CLog::Log(NumOfPlayers);
				countdownTimer = StartCountdown;
				GetWorld()->GetTimerManager().SetTimer(LobbyTimeHandle, this, &ALobbyGameMode::CountDown, 1.0f, true, 0);
			}
		}
	}

	ALobbyGameState* lobbyGameState = GetGameState<ALobbyGameState>();

	if (lobbyGameState == nullptr)
	{
		CLog::Log("GameState Nullptr");
		return;
	}

	lobbyGameState->PlayerConnection(NumOfPlayers);
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	ALobbyGameState* lobbyGameState = GetGameState<ALobbyGameState>();
}

void ALobbyGameMode::PlayerLoginInServer_Implementation()
{
	NumOfPlayers++;
}

void ALobbyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALobbyGameMode::CountDown()
{
	ALobbyGameState* lobbyGameState = GetGameState<ALobbyGameState>();

	if (lobbyGameState != nullptr)
	{
		lobbyGameState->CountDown(countdownTimer);
	}

	countdownTimer--;

	if (countdownTimer < 0)
		EnterMap();
}

void ALobbyGameMode::EnterMap()
{
	TWeakObjectPtr<UWorld> World = GetWorld();
	if (World.IsValid())
	{
		//World->ServerTravel(FString("/Game/SW/Maps/TestLevelMap"));
		World->ServerTravel(FString("/Game/Maps/MainMap"));
		CLog::Log("Dedicated Server entered MainMap!!");
	}
}
