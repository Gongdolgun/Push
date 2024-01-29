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
	void UpdateCharacterMovement(const FName& matchState);

	// 24_01_16 문인수
	// 플레이어 리스트 업데이트, 게임모드에서 호출
	UFUNCTION(Server, Reliable)
		void UpdatePlayerList_Server(const TArray<FPlayerList>& PlayerList);

	UFUNCTION(NetMulticast, Reliable)
		void UpdatePlayerList_NMC(const TArray<FPlayerList>& PlayerList);

	UPROPERTY(BlueprintReadWrite)
		class APushGameMode* PushGameMode;

	class APushCharacter* pushCharacter;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class APushGameState* GameState;
	UPROPERTY()
		class AMainHUD* MainHUD;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
		class UResourceComponent* resourceComponent;

	float CurrentTime; // 게임레벨맵에 들어간 시간
	
	FName MatchState;

	bool bEnableSpawn = true;

public:
	float HUDHealth;
	float HUDMaxHealth;
	float TimeLeft;
};