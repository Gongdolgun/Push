#include "GameState/LobbyGameState.h"
#include "HUD/LobbyHUD.h"
#include "Widgets/LobbyCountDown.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PushCharacter.h"
#include "PlayerController/LobbyPlayerController.h"
#include "Global.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

// 개인 작업 부분 Check
void ALobbyGameState::CountDown(int InCountdown)
{
	Count = InCountdown;
	for(APlayerState* player : PlayerArray)
	{
		ALobbyPlayerController* controller = Cast<ALobbyPlayerController>(player->GetOwner());

		if(controller == nullptr)
		{
			CLog::Log("No Controller");
			continue;
		}

		controller->UpdateTimer_Client(InCountdown);
	}
}

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameState, NumofPlayers);
	DOREPLIFETIME(ALobbyGameState, Count);
}

// 개인 작업 부분 Check
void ALobbyGameState::PlayerConnection(int InPlayerNum)
{
	NumofPlayers = InPlayerNum;
	for (APlayerState* player : PlayerArray)
	{
		ALobbyPlayerController* controller = Cast<ALobbyPlayerController>(player->GetOwner());

		if (controller == nullptr)
		{
			continue;
		}

		controller->UpdatePlayerNum_Client(InPlayerNum);
	}
}

