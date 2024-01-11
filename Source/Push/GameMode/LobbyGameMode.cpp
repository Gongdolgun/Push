#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameState.h"
#include "HUD/LobbyHUD.h"
#include "PlayerController/LobbyPlayerController.h"
#include "Utilites/CLog.h"
#include "Widgets/LobbyCountDown.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerLoginInServer_Implementation();

	if (false == IsValid(NewPlayer)) return;

	if(HasAuthority())
	{
		TWeakObjectPtr<UGameInstance> GameInstance = GetGameInstance();
		if (GameInstance.IsValid())
		{
			if (NumOfPlayers == 1) CLog::Log("Num of Players = 1");
			else if (NumOfPlayers == 2) CLog::Log("Num of Players = 2");
			else if (NumOfPlayers == 3) 
			{
				CLog::Log("Num of Players = 3"); 

				//FTimerDelegate delegate;
				//delegate.BindUObject(this, &ALobbyGameMode::EnterMapTimer);
				//GetWorld()->GetTimerManager().SetTimer(LobbyTimeHandle, delegate, 1.0f, true, countdownTimer);

				GetWorld()->GetTimerManager().SetTimer(LobbyTimeHandle, this, &ALobbyGameMode::CountDown, 1.0f, true, 0);
				
			}
		}
	}
}

void ALobbyGameMode::PlayerLoginInServer_Implementation()
{
	NumOfPlayers++;
}

void ALobbyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Server_SendCurrentTimeToClient(GetWorld()->GetTimeSeconds());
}

void ALobbyGameMode::CountDown()
{
	countdownTimer -= 1.0f;

	if (countdownTimer <= 0.0f)
		EnterMap();
}

void ALobbyGameMode::EnterMap()
{
	TWeakObjectPtr<UWorld> World = GetWorld();
	if (World.IsValid())
	{
		World->ServerTravel(FString("/Game/SW/Maps/TestLevelMap"));
		CLog::Log("When 'Num of Players = 3', Dedicated Server entered TestLevelMap!!");
	}
}

void ALobbyGameMode::UpdateTimer_NMC_Implementation(float InTime)
{
	countdownTimer = InTime;
}

void ALobbyGameMode::Server_SendCurrentTimeToClient_Implementation(float CurrentTime)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ALobbyPlayerController* PlayerController = Cast<ALobbyPlayerController>(It->Get());
		if (PlayerController && PlayerController->IsLocalController())
		{
			PlayerController->Client_ReceiveCurrentTimeFromServer(CurrentTime);
		}
	}
}
