#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/** 게임 시작 시 GameMode
 *
 */

UCLASS()
class PUSH_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UFUNCTION(Server, Reliable)
		void PlayerLoginInServer();

	UPROPERTY(EditAnywhere)
		uint8 MaxNumofPlayers = 3;

	UPROPERTY(EditAnywhere)
		uint8 StartCountdown = 5;

	void Tick(float DeltaSeconds) override;

	void CountDown();
	void EnterMap();

private:
	uint8 NumOfPlayers = 0;
	int countdownTimer = 0;
	FTimerHandle LobbyTimeHandle;

};
