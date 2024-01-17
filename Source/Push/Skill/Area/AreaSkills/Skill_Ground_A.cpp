#include "Skill/Area/AreaSkills/Skill_Ground_A.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "Components/SkillComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Skill/SkillData.h"
#include "Skill/Area/PointDecal_Meteor.h"

ASkill_Ground_A::ASkill_Ground_A()
{
	Helpers::CreateComponent(this, &SphereComponent, "Collision", Root);
	SphereComponent->SetSphereRadius(128.0f);

	Helpers::CreateComponent(this, &Particle, "Particle", Root);
	Particle->bAutoActivate = false;
	Particle->SetIsReplicated(true);
}

void ASkill_Ground_A::BeginPlay()
{
	Super::BeginPlay();

	SkillComponent = Helpers::GetComponent<USkillComponent>(Owner);
	if (SkillComponent == nullptr)
		return;

	Particle->SetVisibility(true);
	Particle->Activate(true);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ASkill_Ground_A::OnComponentBeginOverlap);

	OnSkillClicked();
}

void ASkill_Ground_A::OnSkillClicked()
{
	Super::OnSkillClicked();

	DecalLocation = SkillComponent->SpawnLocation - SkillComponent->curSkillData->RelativeLocation;

	FHitResult HitResult;
	TArray<AActor*> ignores;
	ignores.Add(Owner);

	OnSpawnPointDecal(DecalLocation);
}

void ASkill_Ground_A::OnSpawnPointDecal(FVector InLocation)
{
	Super::OnSpawnPointDecal(InLocation);

	// Point Decal Spawn
	FTransform decalTransform;
	decalTransform.SetLocation(InLocation);

	// 테스트용으로 메테오 데칼 스폰
	APointDecal_Meteor* DeferredDecal = Cast<APointDecal_Meteor>(
		Owner->GetWorld()->SpawnActorDeferred<APointDecal_Meteor>(PointDecal_Class, decalTransform));

	if (DeferredDecal != nullptr)
	{
		DeferredDecal->SetDecalTime(0.0f);
		UGameplayStatics::FinishSpawningActor(DeferredDecal, decalTransform);
	}
}

void ASkill_Ground_A::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ASkill_Ground_A::OnDestroy(FVector InLocation)
{
	Super::OnDestroy(InLocation);

	// 폭발 파티클 소환
	if (IsValid(Explosion))
	{
		FTransform explosionTramsform;
		explosionTramsform.SetLocation(InLocation);
		explosionTramsform.SetScale3D(ExplosionScale);
		UGameplayStatics::SpawnEmitterAtLocation(Owner->GetWorld(), Explosion, explosionTramsform);

		Particle->SetActive(false);
	}

}
