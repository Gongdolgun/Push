#include "Components/ResourceComponent.h"

UResourceComponent::UResourceComponent()
{

}

// 2024.01.02 이현중
// 현재 수치에 Value값을 현재HP에 plus 최대값은 0~MaxHP까지
void UResourceComponent::AdjustHP(int InValue)
{
	HP = FMath::Clamp(HP + InValue, 0.0f, MaxHP);
}

void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}

