#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyCountDown.generated.h"

/** Lobby���� ���Ǵ� ����
 *  
 */
UCLASS(Blueprintable)
class PUSH_API ULobbyCountDown : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* playerAmount; // ������ �÷��̾� ��
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* countDown; // ī��Ʈ �ٿ�
	UPROPERTY(BlueprintReadOnly)
	class ALobbyGameState* lobbyGameState;

	UFUNCTION()
	void UpdateWidget(int currTime);

	UFUNCTION()
	void PlayerAmountText();
	UFUNCTION()
	void CountDownText();

};
