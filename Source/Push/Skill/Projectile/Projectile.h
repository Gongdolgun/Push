#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "Projectile.generated.h"

UCLASS()
class PUSH_API AProjectile : public ASkill
{
	GENERATED_BODY()

public:
	AProjectile();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
public:
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileComponent;

public:
	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		float Gravity_Scale;
};
