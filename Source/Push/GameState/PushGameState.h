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
	UFUNCTION(BlueprintCallable)
		void AddToRank(class APushPlayerController* InController);

	UFUNCTION()
		void UpdateGameNum(uint8 InNumofGames);

	UFUNCTION()
		void ShowTotalRank();

	void GiveGold(TArray<int32> InGoldAmount, int32 InBaseMoney);

	UPROPERTY(VisibleAnywhere, Replicated)
		TArray<class APushPlayerController*> RoundRank;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class URank> RankWidget;
};