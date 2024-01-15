#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

/** Lobby에 사용되는 Lobby Game State
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
	int currentNumOfPlayers; // 현재 접속한 플레이어 수

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MatchStartCountdown)
	int MatchStartCountdown = 20; // 시간 카운트 변수 5, 4, 3, 2, 1

	UFUNCTION()
	void OnRep_MatchStartCountdown(); // MatchStartCountdown 변수가 변경되면 호출되는 함수

	void MatchCountDown(); // SetTimer로 시간 카운팅하는 함수
	void CountDown();

	FTimerHandle LobbyTimeHandle;


	UFUNCTION()
	void UpdateMatchStartCountdownWidget(); // lobbyHUD->위젯에 시간 카운팅 변수를 넘겨 '현재 플레이어 수 & 시간 카운팅'을 업데이트하는 함수

};
