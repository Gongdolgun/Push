#include "Buffs/BuffInstance_Freezing.h"

#include "GameFramework/Character.h"
#include "Components/MoveComponent.h"
#include "Global.h"
#include "Character/AnimInstance_PushCharacter.h"

void ABuffInstance_Freezing::OnEffect()
{
	Super::OnEffect();

	Test_S();
}

void ABuffInstance_Freezing::OffEffect()
{	
	//Super::OffEffect();

	Test_S();

	UMoveComponent* MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	UAnimInstance_PushCharacter* AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (!MoveComponent)
		return;

	MoveComponent->Move();

	MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr)
		return;

	AnimInstance->IsSnapshot = false;
	MoveComponent->Move();
}

void ABuffInstance_Freezing::Test_S_Implementation()
{
	Test_N();
}

void ABuffInstance_Freezing::Test_N_Implementation()
{
	if (!Owner.IsValid())
		return;
	UMoveComponent* MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	UAnimInstance_PushCharacter* AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (!MoveComponent)
		return;
	MoveComponent->Stop();
	if (!AnimInstance || !MoveComponent)
		return;

	AnimInstance->SavePoseSnapshot("Freezing");
	AnimInstance->IsSnapshot = true;
	MoveComponent->Stop();
}

