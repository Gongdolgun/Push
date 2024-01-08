#include "Skill/SkillDatas/SkillData_Area.h"

void USkillData_Area::BeginPlay()
{
	Super::BeginPlay();

}

//void USkillData_Area::Play(ACharacter* InOwner)
//{
//	Super::Play(InOwner);
//
//	// Decal Class »ý¼º
//	if(bDecal == false)
//	{
//		bDecal = true;
//		if (DecalClass == nullptr)
//		{
//			PointDecal = GetWorld()->SpawnActor(DecalClass);
//		}
//	}
//
//	else
//	{
//		bDecal = false;
//		SpawnLocation = PointDecal->GetActorLocation();
//		PointDecal->Destroy();
//	}
//}
