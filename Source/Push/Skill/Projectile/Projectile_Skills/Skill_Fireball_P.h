#pragma once

#include "CoreMinimal.h"
#include "Skill/Projectile/Projectile.h"
#include "Skill_Fireball_P.generated.h"

UCLASS()
class PUSH_API ASkill_Fireball_P : public AProjectile
{
	GENERATED_BODY()
	
public:
	ASkill_Fireball_P();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
