#include "Skill/SkillDatas/SkillData_Projectile.h"
#include "GameFramework/Character.h"

void USkillData_Projectile::Play(ACharacter* InOwner)
{
	Super::Play(InOwner);
	SpawnLocation = InOwner->GetActorLocation();
	InOwner->PlayAnimMontage(ActionMontage, PlayRate);
}