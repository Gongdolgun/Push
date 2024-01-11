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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	float CurrentServerTime;

	////**
	//void UpdateMatchStartCountdownWidget();

	//UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_MatchStartCountdown)
	//float MatchStartCountdown;

	//UFUNCTION()
	//void OnRep_MatchStartCountdown();

	//void MatchCountDown();
	////**


	//UFUNCTION(Server, Reliable)
	//	void Server_SendCurrentTimeToClient(float CurrentTime);

	//UFUNCTION(Client, Reliable)
	//	void Client_ReceiveCurrentTimeFromServer(float CurrentTime);
};
