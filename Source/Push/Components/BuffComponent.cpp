
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

	//2024.01.05 이현중
	//적용된 버프가 없으면 제거
	if (Buffs.Num() < 1)
		return;


	//2024.01.05 이현중
	//버프의 시간진행, 지속시간이 끝난 버프는 종료
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

//2024.01.05 이현중
//버프 자료형을 집어넣으면 그에 따른 클래스를 생성후 OnEffect를 발생
void UBuffComponent::AddBuff(TSubclassOf<UBuffInstance> BuffClass)
{
	if (!Owner)
		return;

	UBuffInstance* temp = NewObject<UBuffInstance>(Owner, BuffClass);
	temp->SetOwner(Owner);
	temp->OnEffect();
	Buffs.Add(temp);
}

