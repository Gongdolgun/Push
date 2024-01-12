#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

UCLASS()
class PUSH_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void PlayerConnection();

	UFUNCTION(NetMulticast, Reliable)
		void SetNumofPlayers_NMC(int InNum);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int currentNumOfPlayers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int minimumNumOfPlayers = 3;

	void MatchCountDown();
	void CountDown();

	FTimerHandle LobbyTimeHandle;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MatchStartCountdown)
		int MatchStartCountdown = 20; 

	UFUNCTION()
		void OnRep_MatchStartCountdown();

	UFUNCTION()
		void UpdateMatchStartCountdownWidget();

};