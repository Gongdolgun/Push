#include "Notifies/Notify/NF_SpawnSkill.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkillComponent.h"
#include "Skill/Skill.h"
#include "Skill/SkillData.h"
#include "Skill/SkillDatas/SkillData_Projectile.h"

FString UNF_SpawnSkill::GetNotifyName_Implementation() const
{
	return "Spawn Skill";
}

void UNF_SpawnSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr || Owner->HasAuthority() == true)
		return;

	USkillComponent* SkillComponent =  Helpers::GetComponent<USkillComponent>(Owner);

	if (SkillComponent == nullptr)
		return;

	FVector SpawnLocation, RelativeSpawnLocation;

	TSubclassOf<ASkill> SpawnSkill = SkillComponent->curSkillData->Skill;

	USkillData_Projectile* SkillData = Cast<USkillData_Projectile>(SkillComponent->curSkillData);
	if (SkillData != nullptr)
	{
		SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * SkillComponent->curSkillData->RelativeDistance;
	}
	else
	{
		RelativeSpawnLocation = SkillComponent->SpawnLocation - Owner->GetActorLocation();
		SpawnLocation = Owner->GetActorLocation() + RelativeSpawnLocation + Owner->GetActorForwardVector() * SkillComponent->curSkillData->RelativeDistance;
	}

	FRotator SpawnRotation = Owner->GetActorForwardVector().Rotation();

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Owner->GetWorld()->SpawnActor<ASkill>(SpawnSkill, SpawnLocation, SpawnRotation, params);
}