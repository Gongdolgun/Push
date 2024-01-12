#include "Widgets/LobbyCountDown.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/TextBlock.h"
#include "GameState/LobbyGameState.h"
#include "Kismet/GameplayStatics.h"

void ULobbyCountDown::UpdateCountdown(float InTime)
{
	CountdownNum->SetText(UKismetTextLibrary::Conv_FloatToText(InTime, ERoundingMode::ToZero));

	lobbyGameState = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this));
}

void ULobbyCountDown::UpdateWidget(int currTime)
{
	if (currTime == 0)
	{
		RemoveFromParent();
	}
	else
	{
		countDown->SetText(FText::FromString(FString::FromInt(currTime)));
	}
}

UTextBlock* ULobbyCountDown::GetPlayerAmountText()
{
	if (lobbyGameState == nullptr) return nullptr;

	//playerAmount = lobbyGameState->currentNumOfPlayers;

	return nullptr;
}

UTextBlock* ULobbyCountDown::GetCountDownText()
{
	if (lobbyGameState == nullptr) return nullptr;

	return nullptr;
}