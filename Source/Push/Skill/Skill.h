#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
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

protected:
	class ACharacter* Owner;

private:
	

};
