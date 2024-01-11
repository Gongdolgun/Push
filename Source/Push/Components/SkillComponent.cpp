#include "Components/SkillComponent.h"
<<<<<<< Updated upstream
=======
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Skill/SkillData.h"
#include "Skill/Skill.h"
#include "Skill/SkillDatas/SkillData_Projectile.h"
#include "Global.h"
>>>>>>> Stashed changes

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	if (ss != nullptr)
		curSkillData = NewObject<USkillData>(Owner, ss);
}


void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

<<<<<<< Updated upstream
}
=======
}

void USkillComponent::UseSkill(char InChar)
{
	if (!SkillMap.Contains(InChar))
		return;

	// curSkillData = SkillMap[InChar];
	Execute();
}

void USkillComponent::Execute()
{
	curSkillData->Play(Owner);
}

void USkillComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USkillComponent, SpawnLocation);
}

>>>>>>> Stashed changes
