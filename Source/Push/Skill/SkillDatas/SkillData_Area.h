#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillData.h"
#include "SkillData_Area.generated.h"

UCLASS(Blueprintable)
class PUSH_API USkillData_Area : public USkillData
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Decal Class")
		TSubclassOf<AActor> DecalClass;

	UPROPERTY(VisibleAnywhere)
		AActor* PointDecal;

	UPROPERTY(VisibleAnywhere)
		bool bDecal;

public:
	virtual void Play(ACharacter* InOwner) override;
};
