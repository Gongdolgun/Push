#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Area.generated.h"

UCLASS(Abstract)
class PUSH_API AArea : public ASkill
{
	GENERATED_BODY()

public:
	AArea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void OnSkillPressed() override;
	virtual void OnSkillClicked() override;

	virtual void OnDestroy(FVector InLocation = FVector::ZeroVector) {};

protected:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Particle")
		class UParticleSystemComponent* Particle;

protected:
	UPROPERTY(BlueprintReadWrite)
		FVector DecalLocation;

	bool bShowDecal = false;
};