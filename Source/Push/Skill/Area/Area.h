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
	virtual void OnSkillPressed() override;
	virtual void OnSkillClicked() override;

	FORCEINLINE virtual bool GetSkillPressed() { return bShowDecal; }
	FORCEINLINE virtual void SetSkillPressed(bool bSkillPrssed) { bShowDecal = bSkillPrssed; }

	virtual void TraceDecal();

	

protected:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Decal")
		class UDecalComponent* Decal_Cursor;

	UPROPERTY(EditAnywhere, Category = "Particle")
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere, Category = "Debug")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug_Decal;

	UPROPERTY(EditAnywhere, Category = "Debug")
		TEnumAsByte<ETraceTypeQuery> TraceType = TraceTypeQuery2;

	UPROPERTY(EditAnywhere, Category = "Debug")
		float MaxDistance = 2000.0f;

protected:
	FVector DecalLocation;
	bool bShowDecal = false;


};