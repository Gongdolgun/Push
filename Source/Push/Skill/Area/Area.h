#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Area.generated.h"

UCLASS(Blueprintable)
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
	virtual void SkillPressed() override;

private:
	UPROPERTY(EditAnywhere, Category = "Decal")
		UMaterialInterface* Decal;

	UPROPERTY(EditAnywhere, Category = "Debug")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

	UPROPERTY(EditAnywhere, Category = "Debug")
		TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere, Category = "Debug")
		float MaxDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
		FVector DecalScale = FVector(0.3f);


};