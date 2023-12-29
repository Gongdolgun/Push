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
	virtual void OnSkillPressed() override;
	virtual void TraceDecal() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnSkillClicked() override;

private:
	UPROPERTY(EditAnywhere, Category = "Meteor")
		class UParticleSystem* Meteor;

	UPROPERTY(EditAnywhere, Category = "Meteor")
		TSubclassOf<class AActor> SubclassSkill;

	TWeakObjectPtr<class ASkill_Decal_A> Meteor_Decal;

};
