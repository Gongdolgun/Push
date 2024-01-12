#include "Buffs/BuffInstance_FastMove.h"
#include "Components/MoveComponent.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABuffInstance_FastMove::OnEffect()
{
	Super::OnEffect();

	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
	movementComponent = Helpers::GetComponent<UCharacterMovementComponent>(Owner.Get());

	if (!moveComponent || !movementComponent)
		return;

	//속도 상승
	moveComponent->SetSpeedPercent_Server(moveComponent->GetSpeedPercent() + PlusSpeedPercent);
	moveComponent->UpdateSpeed_Server();
}

void ABuffInstance_FastMove::OffEffect()
{
	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());

	if (!moveComponent)
		return;

	//속도 감속
	moveComponent->SetSpeedPercent_Server(moveComponent->GetSpeedPercent() - PlusSpeedPercent);
	moveComponent->UpdateSpeed_Server();

	Super::OffEffect();
}

void ABuffInstance_FastMove::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
