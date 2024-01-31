#pragma once

#include "CoreMinimal.h"
#include "Skill/Area/Area.h"
#include "Skill_Ground_A.generated.h"

UCLASS()
class PUSH_API ASkill_Ground_A : public AArea
{
	GENERATED_BODY()

public:
	ASkill_Ground_A();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnSkillClicked() override; 

	virtual void OnSpawnPointDecal(FVector InLocation) override;
	virtual void OnDestroy(FVector InLocation) override;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	class USkillComponent* SkillComponent;
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileComponent;
	UPROPERTY(EditAnywhere, Category = "Particle")
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere, Category = "Particle")
		class UParticleSystem* Explosion;
	UPROPERTY(EditAnywhere, Category = "Particle")
		FVector ExplosionScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere, Category = "PointDecal")
		TSubclassOf<class APointDecal> PointDecal_Class;

};