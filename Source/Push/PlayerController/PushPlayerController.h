#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PushPlayerController.generated.h"

/** PlayerController
 *  HUD를 Update 한다.
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

	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDTime();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable) // Client RPC
	void ClientCheckMatchState(); // Client가 게임에 들어왔을때 Client에게 MatchState을 알리는 함수

private:
	UPROPERTY()
	class APushGameState* GameState;
	UPROPERTY()
	class AMainHUD* MainHUD;
	UPROPERTY()
	class UResourceComponent* resourceComponent;

	float LevelStartingTime; // 게임레벨맵에 들어간 시간
	float WarmupTime;	// 대기 시간
	float MatchTime;		// 경기 시간
	float ResultTime;	// 결과 시간
	float tempTime;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState) 
	FName MatchState;

	UFUNCTION()
	void OnRep_MatchState();

public:
	float HUDHealth;
	float HUDMaxHealth;
};