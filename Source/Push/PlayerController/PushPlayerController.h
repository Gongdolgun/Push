#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PushPlayerController.generated.h"

/** PlayerController
 *  HUD�� Update �Ѵ�.
 */

UCLASS()
class PUSH_API APushPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override; // possed�� Pawn�� �����ϴ� �Լ�

	void OnMatchStateSet(FName State);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDTime();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable) // Server RPC
	void ServerCheckMatchState(); // ���� ���� �ð��� �����ϴ� �Լ�. GameMode�� ���� �־��ְ� Client RPC�� ���ϴ� �Լ�

	UFUNCTION(Client, Reliable) // Client RPC
	void ClientJoinMidgame(FName StateOfMatch, float Warmup, float Match, float Result, float StartingTime); // Client�� ���ӿ� �������� Client���� MatchState�� �˸��� �Լ�

private:
	UPROPERTY()
	class AMainHUD* MainHUD;

	float LevelStartingTime = 0.0f; // ���ӷ����ʿ� �� �ð�
	float MatchTime = 5.0f;		// ��� �ð�
	float WarmupTime = 30.0f;	// ��� �ð�
	float ResultTime = 5.0f;  // ��� �ð�

	UPROPERTY(ReplicatedUsing = OnRep_MatchState) // Client�鿡�� Replicated �ǵ��� ����
	FName MatchState; // GameMode.h�� �̸��� ���� MatchState�� �ִ�

	UFUNCTION()
	void OnRep_MatchState();

	float HUDHealth;
	float HUDMaxHealth;
};

