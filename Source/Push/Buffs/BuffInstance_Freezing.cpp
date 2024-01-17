#include "Buffs/BuffInstance_Freezing.h"

#include "GameFramework/Character.h"
#include "Components/MoveComponent.h"
#include "Global.h"
#include "Character/AnimInstance_PushCharacter.h"

void ABuffInstance_Freezing::OnEffect()
{
	Super::OnEffect();
	if (!Owner.IsValid())
		return;

	//Test_S();
	
	UMoveComponent* MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	if (!MoveComponent)
		return;
	MoveComponent->Stop();
	/*AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (!AnimInstance || !MoveComponent)
		return;

	AnimInstance->SavePoseSnapshot("Freezing");
	AnimInstance->IsSnapshot = true;
	MoveComponent->Stop();*/
}

void ABuffInstance_Freezing::OffEffect()
{	
	Super::OffEffect();


	UMoveComponent* MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	if (!MoveComponent)
		return;

	MoveComponent->Move();

	/*MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr)
		return;

	AnimInstance->IsSnapshot = false;
	MoveComponent->Move();*/
}

void ABuffInstance_Freezing::Test_S_Implementation()
{
	CLog::LogAndPrint("Test_S");
	Test_N();
}

void ABuffInstance_Freezing::Test_N_Implementation()
{
	CLog::LogAndPrint("Test_N");
}

