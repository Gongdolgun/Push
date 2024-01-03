#include "Components/ResourceComponent.h"

UResourceComponent::UResourceComponent()
{

}

void UResourceComponent::AdjustHP(int InValue)
{
	HP = FMath::Clamp(HP + InValue, 0.0f, MaxHP);
}


void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}

