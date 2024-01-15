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
		TSubclassOf<AActor> TracePoint_Class;

	UPROPERTY(VisibleAnywhere)
		class ATracePoint* TracePoint;

	UPROPERTY(VisibleAnywhere)
		bool bDecal = false;

	virtual void Destroy_TracePoint() override;

public:
	virtual void Play(ACharacter* InOwner) override;
};
