#include "Widgets/LobbyCountDown.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/TextBlock.h"
#include "GameState/LobbyGameState.h"
#include "Kismet/GameplayStatics.h"

void ULobbyCountDown::UpdateWidget(int currTime)
{
	if(currTime == 0)
	{
		RemoveFromParent();
	}
	else
	{
		PlayerAmountText();
		CountDownText();
	}
}

void ULobbyCountDown::PlayerAmountText()
{
	lobbyGameState = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this));
	if (lobbyGameState == nullptr) return countDown->SetText(FText::FromString("Null Players?!?!"));

	playerAmount->SetText(FText::FromString(FString::FromInt(lobbyGameState->currentNumOfPlayers) + FString(" / 3 players")));

}

void ULobbyCountDown::CountDownText()
{
	lobbyGameState = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this));
	if (lobbyGameState == nullptr) return countDown->SetText(FText::FromString("Null Seconds?!?!"));

	countDown->SetText(FText::FromString(FString::FromInt(lobbyGameState->MatchStartCountdown) + FString(" seconds")));
}
