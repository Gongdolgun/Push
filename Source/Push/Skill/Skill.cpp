#include "Skill.h"
#include "GameFramework/Character.h"

ASkill::ASkill()
{
	PrimaryActorTick.bCanEverTick = true;

	Owner = Cast<ACharacter>(GetOwner());
}

void ASkill::BeginPlay()
{
	Super::BeginPlay();
	

}

void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

