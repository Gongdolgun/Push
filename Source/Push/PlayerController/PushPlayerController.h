#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Structures.h"
#include "PushPlayerController.generated.h"

/** PlayerController
 *  HUD�� UpdatePlayerData �Ѵ�.
 */

UCLASS()
class PUSH_API APushPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override; // possed�� Pawn�� �����ϴ� �Լ�

	void OnMatchStateSet(FName State);

	void SetHUDTime();

	// 24_01_16 ���μ�
	// �÷��̾� ����Ʈ Ŭ���̾�Ʈ���� ������Ʈ
	UFUNCTION(Server, Reliable)
		void UpdatePlayerList_Server(const TArray<FPlayerList>& PlayerList);

	UFUNCTION(NetMulticast, Reliable)
		void UpdatePlayerList_NMC(const TArray<FPlayerList>& PlayerList);


protected:
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable) // Client RPC
		void ClientCheckMatchState(); // Client�� ���ӿ� �������� Client���� MatchState�� �˸��� �Լ�

private:
	UPROPERTY()
		class APushGameState* GameState;
	UPROPERTY()
		class AMainHUD* MainHUD;
	UPROPERTY()
		class UResourceComponent* resourceComponent;

	float LevelStartingTime; // ���ӷ����ʿ� �� �ð�
	float WarmupTime;   // ��� �ð�
	float MatchTime;      // ��� �ð�
	float ResultTime;   // ��� �ð�
	float tempTime;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
		FName MatchState;

	UFUNCTION()
		void OnRep_MatchState();

public:
	float HUDHealth;
	float HUDMaxHealth;

	UPROPERTY(Replicated, BlueprintReadWrite)
		int32 Gold;
};