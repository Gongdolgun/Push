#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PushGameState.generated.h"


UCLASS()
class PUSH_API APushGameState : public AGameState
{
	GENERATED_BODY()

public:
	APushGameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_TimeChanged)
	float WarmupTime; // ���ð� 
	UPROPERTY(ReplicatedUsing = OnRep_TimeChanged)
	float MatchTime; // ���ð�
	UPROPERTY(ReplicatedUsing = OnRep_TimeChanged)
	float ResultTime; // �����ǥ�ð�
	UPROPERTY(ReplicatedUsing = OnRep_TimeChanged)
	float LevelStartingTime; // ���ӷ����ʿ� �� �ð�

	float CountdownTime = 0.0f;

    UFUNCTION()
	void SetTime(float wTime, float mTime, float rTime, float lTime);

    UFUNCTION()
	void OnRep_TimeChanged();


public:
	UFUNCTION(Server, Reliable)
		void AddToRank_Server(class APushPlayerController* InController);

	void GiveGold(TArray<int32> InGoldAmount);

	UPROPERTY(VisibleAnywhere, Replicated)
		TArray<class APushPlayerController*> RoundRank;
};