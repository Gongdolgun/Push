#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyCountDown.generated.h"

/** Lobby에서 사용되는 위젯
 *  
 */
UCLASS(Blueprintable)
class PUSH_API ULobbyCountDown : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* playerAmount; // 입장한 플레이어 수
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* countDown; // 카운트 다운
	UPROPERTY(BlueprintReadOnly)
	class ALobbyGameState* lobbyGameState;

	UFUNCTION()
	void UpdateWidget(int currTime);

	UFUNCTION()
	void PlayerAmountText();
	UFUNCTION()
	void CountDownText();

};
