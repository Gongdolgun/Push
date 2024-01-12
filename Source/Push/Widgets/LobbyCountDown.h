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
	void UpdateCountdown(float InTime);


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountdownNum; // 5초 카운트 다운

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* countDown; // 카운트 다운
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* playerAmount; // 입장 플레이어
	UPROPERTY(BlueprintReadOnly)
	class ALobbyGameState* lobbyGameState;

	UFUNCTION()
	void UpdateWidget(int currTime);


	UFUNCTION()
	UTextBlock* GetPlayerAmountText();

	UFUNCTION()
	UTextBlock* GetCountDownText();

};
