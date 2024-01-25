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
	// �÷��̾� ����Ʈ ������Ʈ, ���Ӹ�忡�� ȣ��
	UFUNCTION(Server, Reliable)
		void UpdatePlayerList_Server(const TArray<FPlayerList>& PlayerList);

	UFUNCTION(NetMulticast, Reliable)
		void UpdatePlayerList_NMC(const TArray<FPlayerList>& PlayerList);

	UPROPERTY(BlueprintReadWrite)
		class APushGameMode* PushGameMode;

	UFUNCTION(Server, Reliable)
		void ShowKillLog_Server(const FString& InKillPlayer, const FString& InDeadPlayer);

	UFUNCTION(NetMulticast, Reliable)
		void ShowKillLog_NMC(const FString& InKillPlayer, const FString& InDeadPlayer);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable) // Client RPC
		void ClientCheckMatchState(); // Client�� ���ӿ� �������� Client���� MatchState�� �˸��� �Լ�

private:
	UPROPERTY()
		class APushGameState* GameState;
	UPROPERTY()
		class AMainHUD* MainHUD;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
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
};