#include "Components/ShopComponent.h"

UShopComponent::UShopComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UShopComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}