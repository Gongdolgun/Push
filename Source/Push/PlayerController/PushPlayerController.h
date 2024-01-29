#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Structures.h"
#include "PushPlayerController.generated.h"

/** PlayerController
 *  HUD를 UpdatePlayerData 한다.
 */

UCLASS()
class PUSH_API APushPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override; // possed된 Pawn에 접근하는 함수

	void OnMatchStateSet(FName State);

	void SetHUDTime();

	// 24_01_16 문인수
	// 플레이어 리스트 업데이트, 게임모드에서 호출
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
		void ClientCheckMatchState(); // Client가 게임에 들어왔을때 Client에게 MatchState을 알리는 함수

private:
	UPROPERTY()
		class APushGameState* GameState;
	UPROPERTY()
		class AMainHUD* MainHUD;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
		class UResourceComponent* resourceComponent;

	float LevelStartingTime; // 게임레벨맵에 들어간 시간
	float WarmupTime;   // 대기 시간
	float MatchTime;      // 경기 시간
	float ResultTime;   // 결과 시간
	float tempTime;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
		FName MatchState;

	UFUNCTION()
		void OnRep_MatchState();

public:
	float HUDHealth;
	float HUDMaxHealth;
};