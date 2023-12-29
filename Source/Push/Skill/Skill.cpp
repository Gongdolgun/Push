#include "Skill.h"
#include "GameFramework/Character.h"

ASkill::ASkill()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASkill::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	

}

void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


