#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Skill/Area/Area.h"
#include "Skill_Meteor_A.generated.h"

UCLASS(Blueprintable)
class PUSH_API ASkill_Meteor_A : public AArea
{
	GENERATED_BODY()

public:
	ASkill_Meteor_A();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	
	virtual void TraceDecal() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnSkillClicked() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnSkillPressed() override;

	// Particle 충돌 처리 함수
	UFUNCTION()
		void OnParticleCollide(FName EventName, float EmitterTime, int32 ParticleTime,
			FVector Location, FVector Velocity, FVector Direction,
			FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat);

	// 메테오 시작
	UFUNCTION()
		void OnVisibleMeteor();

private:
	UPROPERTY(EditAnywhere, Category = "Meteor")
		TSubclassOf<class AActor> Decal_Class;

	UPROPERTY(EditAnywhere, Category = "Meteor")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug_Particle;

	TWeakObjectPtr<class ASkill_Decal_A> Meteor_Decal;

};
