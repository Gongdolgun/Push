#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyCountDown.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PUSH_API ULobbyCountDown : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountdownNum; // 5초 카운트 다운

public:
	void UpdateCountdown(float InTime);
};
