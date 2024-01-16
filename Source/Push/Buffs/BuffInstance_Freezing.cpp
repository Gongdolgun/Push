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

	OnSnapshot_Server();
}

void ABuffInstance_Freezing::OffEffect()
{
	Super::OffEffect();
	OffSnapshot_Server();
}

void ABuffInstance_Freezing::OnSnapshot_Server_Implementation()
{
	OnSnapshot_NMC();
}

void ABuffInstance_Freezing::OnSnapshot_NMC_Implementation()
{
	MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr || MoveComponent == nullptr)
		return;

	AnimInstance->SavePoseSnapshot("Freezing");
	AnimInstance->IsSnapshot = true;
	MoveComponent->Stop();
}

void ABuffInstance_Freezing::OffSnapshot_Server_Implementation()
{
	OffSnapshot_NMC();
}

void ABuffInstance_Freezing::OffSnapshot_NMC_Implementation()
{
	MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr)
		return;

	AnimInstance->IsSnapshot = false;
	MoveComponent->Move();

}
