#include "Skill.h"
#include "GameFramework/Character.h"

ASkill::ASkill()
{
	PrimaryActorTick.bCanEverTick = true;

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


