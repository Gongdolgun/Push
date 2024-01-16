#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Skill/Area/Area.h"
#include "Skill_Meteor_A.generated.h"

UCLASS(Blueprintable)
class PUSH_API ASkill_Meteor_A : public AArea
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
		class UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Meteor")
		TSubclassOf<class AActor> Decal_Class;

	UPROPERTY(EditAnywhere, Category = "Meteor", DisplayName = "Meteor_Collision")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug_Particle;

	UPROPERTY(EditAnywhere, Category = "Particle")
		class UParticleSystem* Explosion;

public:
	ASkill_Meteor_A();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
		virtual void OnSkillPressed() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnSkillClicked() override;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnDestroy(FVector InLocation) override;

	UFUNCTION(Server, Reliable)
		void Projectile_Server(FVector InVelocity);

	UFUNCTION(NetMulticast, Reliable)
		void Projectile_NMC(FVector InVelocity);

private:
	TWeakObjectPtr<class APointDecal> PointDecal;

	UPROPERTY(EditAnywhere, Category = "Particle")
		FVector ExplosionScale = FVector(1,1,1);

};
