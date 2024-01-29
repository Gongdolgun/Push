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
	void UpdateCharacterMovement(const FName& matchState);

	// 24_01_16 ���μ�
	// �÷��̾� ����Ʈ ������Ʈ, ���Ӹ�忡�� ȣ��
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

	float CurrentTime; // ���ӷ����ʿ� �� �ð�
	
	FName MatchState;

	bool bEnableSpawn = true;

public:
	float HUDHealth;
	float HUDMaxHealth;
	float TimeLeft;
};