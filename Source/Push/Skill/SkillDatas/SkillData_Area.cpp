#include "Skill/SkillDatas/SkillData_Area.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "Components/SkillComponent.h"
#include "Skill/Area/TracePoint.h"

void USkillData_Area::BeginPlay()
{
	Super::BeginPlay();

}

void USkillData_Area::Play(ACharacter* InOwner)
{
	Super::Play(InOwner);

	APushCharacter* character = Cast<APushCharacter>(InOwner);

	if (character == nullptr)
		return;

	USkillComponent* skillComponent = Helpers::GetComponent<USkillComponent>(InOwner);

	if (skillComponent == nullptr)
		return;

	FTransform traceTransform;
	traceTransform.SetLocation(character->GetActorLocation());
	traceTransform.SetRotation(FQuat(character->GetActorRotation()));

	FActorSpawnParameters params;
	params.Owner = character;

	// Decal Class »ý¼º
	if(bDecal == false)
	{
		bDecal = true;

		TracePoint = Cast<ATracePoint>(GetWorld()->SpawnActor(TracePoint_Class, &traceTransform, params));
	}
	
	else
	{
		bDecal = false;

		FVector StartLocation = TracePoint->GetTraceLocation() + RelativeLocation;

		character->SetSpawnlocationRep(StartLocation);
		character->PlayAnimMontageRep(character, ActionMontage, PlayRate);

		TracePoint->Destroy();
	}
}
