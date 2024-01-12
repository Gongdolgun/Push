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
	class UTextBlock* CountdownNum; // 5�� ī��Ʈ �ٿ�

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* countDown; // ī��Ʈ �ٿ�
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* playerAmount; // ���� �÷��̾�
	UPROPERTY(BlueprintReadOnly)
	class ALobbyGameState* lobbyGameState;

	UFUNCTION()
	void UpdateWidget(int currTime);


	UFUNCTION()
	UTextBlock* GetPlayerAmountText();

	UFUNCTION()
	UTextBlock* GetCountDownText();

};
