#include "Buffs/BuffInstance_FastMove.h"
#include "Components/MoveComponent.h"
#include "Global.h"

void UBuffInstance_FastMove::OnEffect()
{
	Super::OnEffect();

	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());

	if (!moveComponent)
		return;

	//속도 상승
	moveComponent->SetSpeedPercent(moveComponent->GetSpeedPercent() + PlusSpeedPercent);
	moveComponent->UpdateSpeed();
}

void UBuffInstance_FastMove::OffEffect()
{
	Super::OffEffect();


	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());

	if (!moveComponent)
		return;

	//속도 감속
	moveComponent->SetSpeedPercent(moveComponent->GetSpeedPercent() - PlusSpeedPercent);
	CLog::Print("offEffect");
	moveComponent->UpdateSpeed();

	ConditionalBeginDestroy();
}
