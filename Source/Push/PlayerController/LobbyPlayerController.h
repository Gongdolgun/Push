#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

UCLASS()
class PUSH_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SetHUDCountdownTime();
	//void SetHUDCountdownTime(float InTime);

	//UFUNCTION(Client, Reliable) // Client RPC
	//	void ClientCheck();

	
	UFUNCTION(Client, Reliable) // 서버로부터 시간을 수신하는 RPC 함수
	void Client_ReceiveCurrentTimeFromServer(float CurrentTime);

	float ServerTime;

private:
	UPROPERTY()
	class ALobbyGameMode* GameMode;

	UPROPERTY()
	class ALobbyGameState* GameState;

	class ALobbyHUD* LobbyHUD;

	float countdownTimer = 5.f;
	float LevelStartingTime;
};
