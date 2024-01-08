#include "Buffs/BuffInstance_FastMove.h"
#include "Components/MoveComponent.h"
#include "Global.h"

void UBuffInstance_FastMove::OnEffect()
{
	Super::OnEffect();

	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());

	if (!moveComponent)
		return;

	//�ӵ� ���
	moveComponent->SetSpeedPercent(moveComponent->GetSpeedPercent() + PlusSpeedPercent);
	moveComponent->UpdateSpeed();
}

void UBuffInstance_FastMove::OffEffect()
{
	Super::OffEffect();


	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());

	if (!moveComponent)
		return;

	//�ӵ� ����
	moveComponent->SetSpeedPercent(moveComponent->GetSpeedPercent() - PlusSpeedPercent);
	CLog::Print("offEffect");
	moveComponent->UpdateSpeed();

	ConditionalBeginDestroy();
}
