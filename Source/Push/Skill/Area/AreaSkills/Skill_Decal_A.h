#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Skill_Decal_A.generated.h"

UCLASS(Blueprintable)
class PUSH_API ASkill_Decal_A : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkill_Decal_A();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void OnTimelinePlayfromStart();

	UFUNCTION()
		void OnTimelineUpdate(float Value);

	UFUNCTION()
		void OnTimelineFinished();

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Decal")
		class UDecalComponent* Decal_Ground;

private:
	// 타임라인
	UPROPERTY()
		class UTimelineComponent* DecalTimeline;

	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve_DecalGround;

	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent TimelineFinished{};

	class UMaterialInstanceDynamic* Dynamic;

};
