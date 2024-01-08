
#include "Components/BuffComponent.h"
#include "Global.h"

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
}


void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//2024.01.05 ������
	//����� ������ ������ ����
	if (Buffs.Num() < 1)
		return;


	//2024.01.05 ������
	//������ �ð�����, ���ӽð��� ���� ������ ����
	for (UBuffInstance* buff : Buffs)
	{
		buff->curTime += DeltaTime;
		if (buff->curTime > buff->LifeTime)
		{
			if (!buff)
				continue;
			buff->OffEffect();
			Buffs.Remove(buff);
		}
	}
}

//2024.01.05 ������
//���� �ڷ����� ��������� �׿� ���� Ŭ������ ������ OnEffect�� �߻�
void UBuffComponent::AddBuff(TSubclassOf<UBuffInstance> BuffClass)
{
	if (!Owner)
		return;

	UBuffInstance* temp = NewObject<UBuffInstance>(Owner, BuffClass);
	temp->SetOwner(Owner);
	temp->OnEffect();
	Buffs.Add(temp);
}

