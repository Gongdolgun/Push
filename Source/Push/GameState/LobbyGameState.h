#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

/** Lobby�� ���Ǵ� Lobby Game State
 * 
 */
UCLASS()
class PUSH_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void PlayerConnection();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int currentNumOfPlayers; // ���� ������ �÷��̾� ��

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MatchStartCountdown)
	int MatchStartCountdown = 20; // �ð� ī��Ʈ ���� 5, 4, 3, 2, 1

	UFUNCTION()
	void OnRep_MatchStartCountdown(); // MatchStartCountdown ������ ����Ǹ� ȣ��Ǵ� �Լ�

	void MatchCountDown(); // SetTimer�� �ð� ī�����ϴ� �Լ�
	void CountDown();

	FTimerHandle LobbyTimeHandle;


	UFUNCTION()
	void UpdateMatchStartCountdownWidget(); // lobbyHUD->������ �ð� ī���� ������ �Ѱ� '���� �÷��̾� �� & �ð� ī����'�� ������Ʈ�ϴ� �Լ�

};
