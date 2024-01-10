#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Structures.generated.h"

USTRUCT()
struct FProjectileData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Projectile")
        float Speed = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Projectile")
        float Gravity_Scale = 0.0f;

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
    //Character���� ������ ������ ��ġ
    UPROPERTY(EditAnywhere, Category = "Damage")
        float Damage = 0.0f;

<<<<<<< Updated upstream
	//LaunchPercent: �� ������ ���󰡴� Launch ����
	UPROPERTY(EditAnywhere, Category = "Launch")
		float xLaunchPercent = 0.0;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float yLaunchPercent = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float zLaunchPercent = 0.0;
=======
    //LaunchPercent: �� ������ ���󰡴� Launch ����
    UPROPERTY(EditAnywhere, Category = "Launch")
        float xLaunchPower = 0.0;

    UPROPERTY(EditAnywhere, Category = "Launch")
        float zLaunchPower = 0.0;

    //Effect: �ǰ� �� ������ ����Ʈ
    UPROPERTY(EditAnywhere, Category = "Effect")
        class UFXSystemAsset* Effect = nullptr;
>>>>>>> Stashed changes

    //EffectScale: �ǰ� �� ������ ����Ʈ ũ�� ����
    UPROPERTY(EditAnywhere, Category = "Effect")
        FVector EffectScale = FVector(1.0f, 1.0f, 1.0f);

    //Location: �ǰ� �� ������ ����Ʈ�� ���� ��ġ
    UPROPERTY(EditAnywhere, Category = "Effect")
        FVector Location = FVector(0.0f, 0.0f, 0.0f);

    //Sound: �ǰ� �� ������ ����
    UPROPERTY(EditAnywhere, Category = "Sound")
        class USoundWave* Sound = nullptr;

    //Debuffs: �ǰ� �� �����ϴ� �������
    UPROPERTY(EditAnywhere, Category = "Debuff")
        TArray<EDebuff> Debuffs;

public:
<<<<<<< Updated upstream
	//���� Launch��. �̰� �����ٰ� Launch�Լ��� �����ϸ� �˴ϴ�.
	float xLaunchValue = xLaunch * xLaunchPercent / 100.0f;
	float yLaunchValue = yLaunch * yLaunchPercent / 100.0f;
	float zLaunchValue = zLaunch * zLaunchPercent / 100.0f;

private:
	float xLaunch = 500.0f;
	float yLaunch = 500.0f;
	float zLaunch = 500.0f;

=======
    float xLaunch;
    float yLaunch;
    float zLaunch;
>>>>>>> Stashed changes
};

UCLASS()
class PUSH_API UStructures : public UObject
{
    GENERATED_BODY()

};