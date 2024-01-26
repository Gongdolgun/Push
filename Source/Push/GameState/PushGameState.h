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

	UPROPERTY(Replicated)
	float CurrentTime;

    UFUNCTION()
	void SetTime(float InTime);

public:
	UFUNCTION(Server, Reliable)
		void AddToRank_Server(class APushPlayerController* InController);

	void GiveGold(TArray<int32> InGoldAmount);

	UPROPERTY(VisibleAnywhere, Replicated)
		TArray<class APushPlayerController*> RoundRank;
};