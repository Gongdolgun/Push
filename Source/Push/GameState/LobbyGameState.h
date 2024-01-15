#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void PlayerConnection();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentNumOfPlayers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int minimumNumOfPlayers = 3;

	//**
	void MatchCountDown();
	void CountDown();

	FTimerHandle LobbyTimeHandle;
	//**

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MatchStartCountdown)
	int MatchStartCountdown = 20; // 시간 카운트 변수 5, 4, 3, 2, 1

	UFUNCTION()
	void OnRep_MatchStartCountdown();

	UFUNCTION()
	void UpdateMatchStartCountdownWidget();

};
