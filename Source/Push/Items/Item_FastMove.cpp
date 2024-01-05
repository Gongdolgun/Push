#include "Items/Item_FastMove.h"
#include "Global.h"
#include "Buffs/BuffInstance.h"
#include "Components/BuffComponent.h"

void AItem_FastMove::BeginPlay()
{
	AItemBase::BeginPlay();
}

void AItem_FastMove::Tick(float DeltaTime)
{
	AItemBase::Tick(DeltaTime);
}

void AItem_FastMove::Use()
{
	if (Owner == nullptr)
		return;

	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());

	if(!!buffComponent)
	{
		buffComponent->AddBuff(BuffClass);
	}
}
