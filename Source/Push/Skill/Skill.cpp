#include "Skill.h"
<<<<<<< Updated upstream
=======
#include "Components/ShapeComponent.h"
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
#include "Global.h"
>>>>>>> Stashed changes
#include "GameFramework/Character.h"

ASkill::ASkill()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	if (!Owner)
	{
		return;
	}
	

}

void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


