#include "Components/SkillComponent.h"
#include "GameFramework/Character.h"
#include "Skill/SkillData.h"
#include "Skill/SkillDatas/SkillData_Projectile.h"


USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	curSkillData = NewObject<USkillData>(Owner, ss);
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