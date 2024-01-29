#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Misc/Structures.h"
#include "PushGameMode.generated.h"

/** 실제 게임에 사용되는 GameMode
 *  GameMode는 Server에만 존재한다. Client 존재X
 *
 *   대기시간 > 경기시간 > 결과시간
 */

namespace MatchState
{
	extern PUSH_API const FName Round; // 경기시간
}

namespace MatchState
{
	extern PUSH_API const FName Result; // 결과발표
}

UCLASS()
class PUSH_API APushGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APushGameMode();
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 15.0f; // 상점시간 
	UPROPERTY(EditDefaultsOnly)
	float ResultTime = 5.0f; // 결과시간

	float CurrentTime = 0.0f; // 게임레벨맵에 들어간 시간
	float CountdownTime = 0.0f;
	float tempTime = 0.0f;

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:
	FLinearColor Colors[4] = {FLinearColor::Red, FLinearColor::Blue, FLinearColor::Green, FLinearColor::Black};
	uint8 index = 0;
	TArray<class APushPlayerController*> Controllers;

public:
	// 24_01_16 문인수
	UFUNCTION(BlueprintCallable)
		void UpdatePlayerList();

	UPROPERTY(EditAnywhere, Category = "PlayerList")
		TArray<FPlayerList> PlayerListData;

	UPROPERTY(EditAnywhere, Category = "PlayerList")
		TArray<FPlayerList> PlayerListData_Sorted;

	UPROPERTY(BlueprintReadWrite)
		TArray<class APlayerController*> AllPC;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ARing> RingClass; // 경기 중 줄어드는 링

	TWeakObjectPtr<class ARing> Ring;

	FPlayerList PlayerData;

public:
	//24-01-24 서동주 라운드 분할
	UPROPERTY(EditAnywhere)
		TArray<float> RoundTime;

	UPROPERTY(EditAnywhere)
		TArray<float> RingRadius;

	uint8 Round = 0;

	//24-01-24 서동주 골드 관련
	UPROPERTY(EditAnywhere)
		TArray<int32> MoneyPerRank;

	UPROPERTY(EditAnywhere)
		int32 BaseMoney = 10;

	virtual void SetMatchState(FName NewState) override;

	class APushGameState* PushGameState;
};