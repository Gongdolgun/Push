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
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override; // possed된 Pawn에 접근하는 함수

	void SetHUDTime();

	// 24_01_16 문인수
	// 플레이어 리스트 업데이트, 게임모드에서 호출
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

	float CurrentTime; // 게임레벨맵에 들어간 시간

	FName MatchState;

public:
	float HUDHealth;
	float HUDMaxHealth;
	float TimeLeft;
};