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

void AItem_FastMove::UseItem_Implementation()
{
	Super::UseItem_Implementation();
	if (!Owner.IsValid())
		return;
	APlayerController* controller = Cast<APlayerController>(Owner->GetController());

	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());

	if (!!buffComponent)
	{
		buffComponent->AddBuff(BuffClass);
		Destroy();
	}
}


//void AItem_FastMove::UseItem_Implementation()
//{
//}
