#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PushGameMode.generated.h"

/** ���� ���ӿ� ���Ǵ� GameMode
 *  GameMode�� Server���� �����Ѵ�. Client ����X
 *
 *   ���ð� > ���ð� > ����ð�
 */

namespace MatchState
{
	extern PUSH_API const FName Result; // �����ǥ
}

UCLASS()
class PUSH_API APushGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APushGameMode();
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly, Replicated)
		float WarmupTime = 5.0f; // ���ð� 

	UPROPERTY(EditDefaultsOnly, Replicated)
		float MatchTime = 30.0f; // ���ð�

	UPROPERTY(EditDefaultsOnly, Replicated)
		float ResultTime = 5.0f; // �����ǥ�ð�

	UPROPERTY(EditDefaultsOnly, Replicated)
	float LevelStartingTime = 0.0f; // ���ӷ����ʿ� �� �ð�

	float CountdownTime = 0.0f;
	float tempTime = 0.0f;

protected:
	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(Server, Reliable)
	void PlayerLoginInServer();

private:
	uint8 NumOfPlayers = 0;


	FLinearColor Colors[4] = {FLinearColor::Red, FLinearColor::Blue, FLinearColor::Green, FLinearColor::Black};
	uint8 index = 0;
	TArray<class APushPlayerController*> Controllers;
};