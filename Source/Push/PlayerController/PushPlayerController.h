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

	void Init();
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDTime();


protected:
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable) // Client RPC
		void ClientCheckMatchState(); // Client��	 ���ӿ� �������� Client���� MatchState�� �˸��� �Լ�

private:
	UPROPERTY()
		class AMainHUD* MainHUD;
	UPROPERTY()
		class UResourceComponent* resourceComponent;

	float LevelStartingTime = 0.0f; // ���ӷ����ʿ� �� �ð�
	float WarmupTime = 0.0f;	// ��� �ð�
	float MatchTime = 0.0f;		// ��� �ð�
	float ResultTime = 0.0f;  // ��� �ð�

	UPROPERTY(ReplicatedUsing = OnRep_MatchState) // Client�鿡�� Replicated �ǵ��� ����
		FName MatchState; // GameMode.h�� �̸��� ���� MatchState�� �ִ�

	UFUNCTION()
		void OnRep_MatchState();

public:
	float HUDHealth;
	float HUDMaxHealth;

public:
	FLinearColor BodyColor;

	UFUNCTION(Server, Reliable)
		void SetBodyColor_Server(FLinearColor InColor);

	UFUNCTION(NetMulticast, Reliable)
		void SetBodyColor_NMC(FLinearColor InColor);
};