#include "Items/Item_FastMove.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MoveComponent.h"

void AItem_FastMove::BeginPlay()
{
	Super::BeginPlay();
}

void AItem_FastMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem_FastMove::Use()
{
	UCharacterMovementComponent* movementComponent = Helpers::GetComponent<UCharacterMovementComponent>(Owner.Get());
	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());

	moveComponent->SetSpeedPercent(moveComponent->GetSpeedPercent() + PlusSpeedPercent);
	moveComponent->UpdateSpeed();
}
