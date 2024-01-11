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
	
	UFUNCTION(Server, Reliable)
		void PlayerLoginInServer();
	
	void Tick(float DeltaSeconds) override;

	void CountDown();
	void EnterMap(); // 경기를 하는 레벨맵

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float countdownTimer = 5.f;

	UFUNCTION(NetMulticast, Reliable)
		void UpdateTimer_NMC(float InTime);

	///////////////////////////////////////
	// 서버에서 클라이언트로 현재 시간을 전송하는 RPC 함수
	UFUNCTION(Server, Reliable)
	void Server_SendCurrentTimeToClient(float CurrentTime);
	/////////////////////////////////////

private:
	uint8 NumOfPlayers = 0;

	FTimerHandle LobbyTimeHandle;
};
