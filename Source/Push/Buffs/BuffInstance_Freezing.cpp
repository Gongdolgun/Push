#include "Buffs/BuffInstance_Freezing.h"

#include "GameFramework/Character.h"
#include "Components/MoveComponent.h"
#include "Global.h"
#include "Character/AnimInstance_PushCharacter.h"

void ABuffInstance_Freezing::OnEffect()
{
	Super::OnEffect();

	FreezeON_Server();
}

void ABuffInstance_Freezing::OffEffect()
{	
	Super::OffEffect();
	FreezeOFF_Server();
}

void ABuffInstance_Freezing::FreezeOFF_Server_Implementation()
{
	FreezeOFF_NMC();
}

void ABuffInstance_Freezing::FreezeOFF_NMC_Implementation()
{
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

void ABuffInstance_Freezing::FreezeON_Server_Implementation()
{
	FreezeON_NMC();
}

void ABuffInstance_Freezing::FreezeON_NMC_Implementation()
{
	CLog::Log("NMC_Freezing");

	if (!Owner.IsValid())
		return;
	UMoveComponent* MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	UAnimInstance_PushCharacter* AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (!MoveComponent)
		return;
	MoveComponent->Stop();
	if (!AnimInstance)
		return;

	AnimInstance->SavePoseSnapshot("Freezing");
	AnimInstance->IsSnapshot = true;
}

