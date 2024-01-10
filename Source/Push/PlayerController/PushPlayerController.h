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
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override; // possed된 Pawn에 접근하는 함수

	void OnMatchStateSet(FName State);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void Init();
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDTime();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable) // Client RPC
		void ClientCheckMatchState(); // Client가	 게임에 들어왔을때 Client에게 MatchState을 알리는 함수

private:
	UPROPERTY()
		class AMainHUD* MainHUD;
	UPROPERTY()
		class UResourceComponent* resourceComponent;

	float LevelStartingTime = 0.0f; // 게임레벨맵에 들어간 시간
	float WarmupTime = 0.0f;	// 대기 시간
	float MatchTime = 0.0f;		// 경기 시간
	float ResultTime = 0.0f;  // 결과 시간

	UPROPERTY(ReplicatedUsing = OnRep_MatchState) // Client들에게 Replicated 되도록 설정
		FName MatchState; // GameMode.h의 이름이 같은 MatchState이 있다

	UFUNCTION()
		void OnRep_MatchState();

	float HUDHealth;
	float HUDMaxHealth;

public:
	FLinearColor BodyColor;

	UFUNCTION(Server, Reliable)
		void SetBodyColor_Server(FLinearColor InColor);

	UFUNCTION(NetMulticast, Reliable)
		void SetBodyColor_NMC(FLinearColor InColor);
};