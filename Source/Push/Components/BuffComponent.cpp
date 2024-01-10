
#include "Components/BuffComponent.h"
#include "Widgets/WDG_BuffBoard.h"
#include "GameFramework/Character.h"
#include "Global.h"

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());

	if (!Owner.IsValid())
		return;

	AController* test = Owner->GetController();

	APlayerController* controller = Cast<APlayerController>(test);

	if (!controller || ! WidgetClass)
		return;

	Widget = CreateWidget<UWDG_BuffBoard>(controller, WidgetClass, "BuffWidgetBoard");
	if(!!Widget)
		Widget->AddToViewport();
}


void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UBuffComponent::AddBuff_Server_Implementation(TSubclassOf<ABuffInstance> BuffClass)
{
	AddBuff_NMC(BuffClass);
}


//2024.01.05 ������
//���� �ڷ����� ��������� �׿� ���� ���͸� ������ OnEffect�� �߻� <- 2024.01.09 ���� Ŭ������������ ���ͻ������� ����
// 2024.01.10 ���� Ŭ���̾�Ʈ������ �Ҵ��ϴ� Add�� ������ ����ϵ��� ����
void UBuffComponent::AddBuff_NMC_Implementation(TSubclassOf<ABuffInstance> BuffClass)
{
	if (!Owner.IsValid())
		return;

	FActorSpawnParameters param;
	param.Owner = Owner.Get();

	ABuffInstance* temp = Cast<ABuffInstance>(Owner->GetWorld()->SpawnActor<ABuffInstance>(BuffClass, param));

	if (!temp || !Widget)
		return;

	temp->OnEffect();
	Widget->AddBuff(temp->GetWidget());
	Buffs.Add(temp);
}

void UBuffComponent::RemoveBuff(ABuffInstance* removeBuff)
{
	if (!Widget)
		return;

	Widget->SubWidget(removeBuff->GetWidget());

	Buffs.Remove(removeBuff);
}


