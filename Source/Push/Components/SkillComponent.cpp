#include "Components/SkillComponent.h"
#include "Net/UnrealNetwork.h"
#include "Skill/SkillData.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

}


void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
	DOREPLIFETIME(USkillComponent, Meteor_StartLocation);
}
