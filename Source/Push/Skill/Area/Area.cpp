#include "Area.h"
#include "Global.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"

AArea::AArea()
{
	Helpers::CreateComponent(this, &Root, "Root", RootComponent);
	Helpers::CreateComponent(this, &Particle, "Particle", Root);

	Particle->bAutoActivate = false;
}

void AArea::BeginPlay()
{
	Super::BeginPlay();


}

void AArea::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void AArea::OnSkillPressed()
{
	Super::OnSkillPressed();


}

void AArea::OnSkillClicked()
{
	Super::OnSkillClicked();

	
}
