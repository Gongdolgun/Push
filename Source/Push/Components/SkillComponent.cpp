#include "Components/SkillComponent.h"
#include "GameFramework/Character.h"
#include "Skill/SkillData.h"
#include "Skill/Skill.h"
#include "Skill/SkillDatas/SkillData_Projectile.h"
#include "Global.h"


USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	/*SetNetAddressable();
	SetIsReplicated(true);*/
}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	if(ss != nullptr)
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

FTransform USkillComponent::GetSpawnTransform()
{
	FVector SpawnLoc = Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 300);
	FRotator SpawnRot = UKismetMathLibrary::MakeRotFromX(Owner->GetActorForwardVector());

	return UKismetMathLibrary::MakeTransform(SpawnLoc, SpawnRot, FVector::OneVector);
}

void USkillComponent::SpawnCallOnServer_Implementation(TSubclassOf<ASkill> SpawnSkill, FVector SpawnLocation,
                                                       FRotator SpawnRotation)
{
	SpawnCallMulticast_Implementation(SpawnSkill, SpawnLocation, SpawnRotation);
}

void USkillComponent::SpawnCallMulticast_Implementation(TSubclassOf<ASkill> SpawnSkill, FVector SpawnLocation,
	FRotator SpawnRotation)
{
	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Owner->GetWorld()->SpawnActor<ASkill>(SpawnSkill, SpawnLocation, SpawnRotation, params);
}