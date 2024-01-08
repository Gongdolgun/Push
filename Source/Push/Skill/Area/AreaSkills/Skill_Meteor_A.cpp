#include "Skill/Area/AreaSkills/Skill_Meteor_A.h"
#include "Global.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Skill/Area/PointDecal.h"

ASkill_Meteor_A::ASkill_Meteor_A()
{
	Helpers::CreateComponent(this, &SphereComponent, "Collision", Root);
	SphereComponent->SetSphereRadius(128.0f);

	Helpers::CreateActorComponent(this, &ProjectileComponent, "ProjectileComponent");
	ProjectileComponent->InitialSpeed = 1000.0f;
	ProjectileComponent->ProjectileGravityScale = 0.0f;

	
}

void ASkill_Meteor_A::BeginPlay()
{
	Super::BeginPlay();

	Particle->SetVisibility(true);
	Particle->Activate(true);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ASkill_Meteor_A::OnComponentBeginOverlap);
}

void ASkill_Meteor_A::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ASkill_Meteor_A::OnSkillPressed()
{
	Super::OnSkillPressed();

	
}

void ASkill_Meteor_A::OnSkillClicked()
{
	Super::OnSkillClicked();

	// Meteor Direction
	Meteor_Location = GetActorLocation();
	Meteor_Direction = DecalLocation - Meteor_Location;
	ProjectileComponent->Velocity = ProjectileComponent->InitialSpeed * (Meteor_Direction.GetSafeNormal());

	// 떨어지는 시간 구하기
	float falling_Distance = FVector::Dist(Meteor_Location, DecalLocation);
	float falling_Speed = ProjectileComponent->Velocity.Size();

	float fallingTime = falling_Distance / falling_Speed;

	// Point Decal Spawn
	FTransform decalTransform;
	decalTransform.SetLocation(DecalLocation);

	 APointDecal* DeferredDecal = Cast<APointDecal>(
		Owner->GetWorld()->SpawnActorDeferred<APointDecal>(Decal_Class, decalTransform));
	
	if (DeferredDecal != nullptr)
	{
		DeferredDecal->SetDecalTime(fallingTime);
		UGameplayStatics::FinishSpawningActor(DeferredDecal, decalTransform);
	}

	
}

void ASkill_Meteor_A::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnDestroy();

	// 땅에 닿을 때, 캐릭터가 아니여야함
	if (!Cast<APawn>(OtherActor))
	{
		FVector start = SweepResult.ImpactNormal;
		FVector end = SweepResult.ImpactNormal;
		float radius = 150.0f;

		// 데미지를 줄 Pawn만 추적
		FHitResult Particle_HitResult;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
		ObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ignores;
		ignores.Add(Owner);

		UKismetSystemLibrary::SphereTraceSingleForObjects(Owner->GetWorld(), start, end, radius, ObjectType,
			false, ignores, DrawDebug_Particle, Particle_HitResult, true);

		if (Particle_HitResult.bBlockingHit)
		{
			// TODO : Hit Interface 데미지 처리
			CLog::Print("Hit");
		}
	}

	
}

void ASkill_Meteor_A::OnDestroy()
{
	Super::OnDestroy();

	// 폭발 파티클 소환
	if (Explosion)
	{
		FTransform explosionTramsform;
		explosionTramsform.SetLocation(DecalLocation);
		explosionTramsform.SetScale3D(ExplosionScale);
		UGameplayStatics::SpawnEmitterAtLocation(Owner->GetWorld(), Explosion, explosionTramsform);
	}

	Particle->SetActive(false);

}
