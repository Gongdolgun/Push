#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/** ���� ���� �� GameMode
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
	void EnterMap(); // ��⸦ �ϴ� ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float countdownTimer = 5.f;

	UFUNCTION(NetMulticast, Reliable)
		void UpdateTimer_NMC(float InTime);

	///////////////////////////////////////
	// �������� Ŭ���̾�Ʈ�� ���� �ð��� �����ϴ� RPC �Լ�
	UFUNCTION(Server, Reliable)
	void Server_SendCurrentTimeToClient(float CurrentTime);
	/////////////////////////////////////

private:
	uint8 NumOfPlayers = 0;

	FTimerHandle LobbyTimeHandle;
};
