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
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override; // possed�� Pawn�� �����ϴ� �Լ�

	void SetHUDTime();

	// 24_01_16 ���μ�
	// �÷��̾� ����Ʈ ������Ʈ, ���Ӹ�忡�� ȣ��
	UFUNCTION(Server, Reliable)
		void UpdatePlayerList_Server(const TArray<FPlayerList>& PlayerList);

	UFUNCTION(NetMulticast, Reliable)
		void UpdatePlayerList_NMC(const TArray<FPlayerList>& PlayerList);

	UFUNCTION(Client, Reliable)
		void UpdateGameNum_Client(uint8 InNumofGames);

	UFUNCTION(Client, Reliable)
		void ShowRank_Client(uint8 InRank, TSubclassOf<class URank> InRankWidget);

	UPROPERTY(BlueprintReadWrite)
		class APushGameMode* PushGameMode;

	UPROPERTY(BlueprintReadWrite)
		class APushGameState* GameState;
public:
	bool operator()(const APushPlayerController* Other);

	UPROPERTY(BlueprintReadWrite)
		class UResourceComponent* resourceComponent;

	UFUNCTION(Server, Reliable)
		void ShowKillLog_Server(const FString& InKillPlayer, const FString& InDeadPlayer);

	UFUNCTION(NetMulticast, Reliable)
		void ShowKillLog_NMC(const FString& InKillPlayer, const FString& InDeadPlayer);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class AMainHUD* MainHUD;

	float CurrentTime; // ���ӷ����ʿ� �� �ð�

	FName MatchState;

public:
	float HUDHealth;
	float HUDMaxHealth;
	float TimeLeft;
};