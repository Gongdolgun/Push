#include "Skill/Area/AreaSkills/Skill_Meteor_A.h"
#include "Global.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TimelineComponent.h"
#include "Skill_Decal_A.h"

ASkill_Meteor_A::ASkill_Meteor_A()
{
	
}

void ASkill_Meteor_A::BeginPlay()
{
	Super::BeginPlay();

	

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

	CLog::Print("Meteor");

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Meteor, DecalLocation);

	FTransform decalTransform;
	decalTransform.SetLocation(DecalLocation);

	FActorSpawnParameters param;
	param.Owner = Owner;

	Meteor_Decal = MakeWeakObjectPtr(
		Owner->GetWorld()->SpawnActor<ASkill_Decal_A>(SubclassSkill, decalTransform, param));

}

void ASkill_Meteor_A::TraceDecal()
{
	Super::TraceDecal();

}