#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Structures.generated.h"

USTRUCT()
struct FHitData
{
	GENERATED_BODY()

public:
	//Character에게 입히는 데미지 수치
	UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 0.0f;

	//LaunchPercent: 각 축으로 날라가는 Launch 비율
	UPROPERTY(EditAnywhere, Category = "Launch")
		float xLaunchPercent = 0.0;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float yLaunchPercent = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float zLaunchPercent = 0.0;

	//Effect: 피격 시 나오는 이펙트
	UPROPERTY(EditAnywhere, Category = "Effect")
		class UFXSystemAsset* Effect = nullptr;

	//EffectScale: 피격 시 나오는 이펙트 크기 비율
	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector EffectScale = FVector(1.0f, 1.0f, 1.0f);

	//Location: 피격 시 나오는 이펙트와 사운드 위치
	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector Location = FVector(0.0f, 0.0f, 0.0f);

	//Sound: 피격 시 나오는 사운드
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundWave* Sound = nullptr;

	//Debuffs: 피격 시 적용하는 디버프들
	UPROPERTY(EditAnywhere, Category = "Debuff")
		TArray<EDebuff> Debuffs;

public:
	//실제 Launch값. 이걸 가져다가 Launch함수에 적용하면 됩니다.
	float xLaunchValue = xLaunch * xLaunchPercent / 100.0f;
	float yLaunchValue = yLaunch * yLaunchPercent / 100.0f;
	float zLaunchValue = zLaunch * zLaunchPercent / 100.0f;

private:
	float xLaunch = 500.0f;
	float yLaunch = 500.0f;
	float zLaunch = 500.0f;

};

UCLASS()
class PUSH_API UStructures : public UObject
{
	GENERATED_BODY()

};
