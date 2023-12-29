#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill.generated.h"

UCLASS(Blueprintable)
class PUSH_API ASkill : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkill();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SkillPressed() {}

protected:
	class ACharacter* Owner;

	

};
