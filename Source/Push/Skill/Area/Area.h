#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
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

private:
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

	UPROPERTY(EditAnywhere)
		float MaxDistance;

};