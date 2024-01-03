#include "Skill/Area/AreaSkills/Skill_Meteor_A.h"
#include "Global.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TimelineComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Particles/ParticleSystem.h"
#include "Skill_Decal_A.h"

ASkill_Meteor_A::ASkill_Meteor_A()
{


}

void ASkill_Meteor_A::BeginPlay()
{
	Super::BeginPlay();

	Particle->OnParticleCollide.AddDynamic(this, &ASkill_Meteor_A::OnParticleCollide);

}

void ASkill_Meteor_A::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ASkill_Meteor_A::OnSkillPressed()
{
	Super::OnSkillPressed();

}

void ASkill_Meteor_A::TraceDecal()
{
	Super::TraceDecal();

}

void ASkill_Meteor_A::OnSkillClicked()
{
	Super::OnSkillClicked();

	OnVisibleMeteor();

	FTransform decalTransform;
	decalTransform.SetLocation(DecalLocation);

	FActorSpawnParameters param;
	param.Owner = Owner;

	Meteor_Decal = MakeWeakObjectPtr(
		Owner->GetWorld()->SpawnActor<ASkill_Decal_A>(Decal_Class, decalTransform, param));

	
}

void ASkill_Meteor_A::OnParticleCollide(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location,
	FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat)
{
	// Particle 面倒 贸府

	FVector start = Location;
	FVector end = Location;
	float radius = 150.0f;

	FHitResult Particle_HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ignores;
	ignores.Add(Owner);

	UKismetSystemLibrary::SphereTraceSingleForObjects(Owner->GetWorld(), start, end, radius, ObjectType, 
		false, ignores, DrawDebug_Particle, Particle_HitResult, true);

	if (Particle_HitResult.bBlockingHit)
	{
		// TODO : Hit Interface 单固瘤 贸府
		CLog::Print("Hit");
	}


}

void ASkill_Meteor_A::OnVisibleMeteor()
{
	Particle->SetWorldLocation(DecalLocation);
	Particle->SetWorldRotation(Owner->GetActorRotation());

	Particle->Activate(true);
	Particle->SetVisibility(true);
}


