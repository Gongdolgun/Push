
#include "Components/ItemComponent.h"
#include "Items/ItemBase.h"
#include "Global.h"
#include "Items/Item_FastMove.h"

UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UItemComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
}


void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//아이템 사용
void UItemComponent::UseItem()
{
	FActorSpawnParameters param;
	param.Owner = Owner.Get();
	Item = Cast<AItemBase>(Owner->GetWorld()->SpawnActor(ItemClass, 0, 0, param));

	if (!Item.IsValid())
		return;

	Item->Use();
}

void UItemComponent::DestroyItem()
{
	if (!Item.IsValid())
		return;
	Item->Destroy();
}

