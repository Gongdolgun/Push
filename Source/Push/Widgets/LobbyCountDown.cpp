#include "Widgets/LobbyCountDown.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/TextBlock.h"

void ULobbyCountDown::UpdateCountdown(float InTime)
{
	CountdownNum->SetText(UKismetTextLibrary::Conv_FloatToText(InTime, ERoundingMode::ToZero));
}
