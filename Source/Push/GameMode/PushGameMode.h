#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
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
	float WarmupTime = 5.0f; // 대기시간 
	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 30.0f; // 경기시간
	UPROPERTY(EditDefaultsOnly)
	float ResultTime = 5.0f; // 결과발표시간

	float LevelStartingTime = 0.0f; // 게임레벨맵에 들어간 시간

	float CountdownTime = 0.0f;
	float tempTime = 0.0f;

protected:
	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	FLinearColor Colors[4] = {FLinearColor::Red, FLinearColor::Blue, FLinearColor::Green, FLinearColor::Black};
	uint8 index = 0;
	TArray<class APushPlayerController*> Controllers;

};