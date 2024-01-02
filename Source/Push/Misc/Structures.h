#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Structures.generated.h"

USTRUCT()
struct FHitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float xLaunchPercent = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float yLaunchPercent = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float zLaunchPercent = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		float EffectSize = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundWave* Sound;

	UPROPERTY(EditAnywhere, Category = "Debuff")
		TArray<EDebuff> Debuffs;

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
