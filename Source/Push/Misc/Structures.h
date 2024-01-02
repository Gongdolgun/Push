#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Structures.generated.h"

// 231229 이민학
// Projectile 스킬 구조체
USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Projectile")
		float Speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float Gravity_Scale = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float Damage = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		bool CanRotate = false;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float InterpSpeed = 2.0f;
};

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
		class UFXSystemAsset* Effect;

	//EffectSize: 피격 시 나오는 이펙트 크기 비율
	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector EffectSize = FVector(1.0f, 1.0f, 1.0f);

	//Sound: 피격 시 나오는 사운드
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundWave* Sound;

	//Debuffs: 피격 시 적용하는 디버프들
	UPROPERTY(EditAnywhere, Category = "Debuff")
		TArray<EDebuff> Debuffs;

public:
	float xLaunchValue = xLaunch * xLaunchPercent / 100.0f;
	float yLaunchValue = yLaunch * yLaunchPercent / 100.0f;
	float zLaunchValue = zLaunch * zLaunchPercent / 100.0f;

private:
	float xLaunch = 500.0f;
	float zLaunch = 500.0f;
	float yLaunch = 500.0f;

};

UCLASS()
class PUSH_API UStructures : public UObject
{
	GENERATED_BODY()

};
