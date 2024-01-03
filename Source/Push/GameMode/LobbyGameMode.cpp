#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	TWeakObjectPtr<UGameInstance> GameInstance = GetGameInstance();
	if (GameInstance.IsValid())
	{
		TWeakObjectPtr<UWorld> World = GetWorld();
		if (World.IsValid())
		{
			World->ServerTravel(FString("/Game/Maps/ThirdPersonExampleMap"));
		}
	}
}
