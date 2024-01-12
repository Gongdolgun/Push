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

	//UFUNCTION(Client, Reliable) // Client RPC
	//	void ClientCheck();

private:
	UPROPERTY()
	class ALobbyGameState* GameState;

	class ALobbyHUD* LobbyHUD;

	float countdownTimer = 5.f;
	float LevelStartingTime;
};
