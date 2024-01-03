#include "Components/ResourceComponent.h"

UResourceComponent::UResourceComponent()
{

}

// 2024.01.02 ������
// ���� ��ġ�� Value���� ����HP�� plus �ִ밪�� 0~MaxHP����
void UResourceComponent::AdjustHP(int InValue)
{
	HP = FMath::Clamp(HP + InValue, 0.0f, MaxHP);
}

void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}

