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
	float TempTime;
	UPROPERTY(ReplicatedUsing = OnRep_TimeChanged)
	float CountdownTime;

    UFUNCTION()
	void SetTime(float cdTime, float tmTime);

    UFUNCTION()
	void OnRep_TimeChanged();


public:
	UFUNCTION(Server, Reliable)
		void AddToRank_Server(class APushPlayerController* InController);

	void GiveGold(TArray<int32> InGoldAmount);

	UPROPERTY(VisibleAnywhere, Replicated)
		TArray<class APushPlayerController*> RoundRank;
};