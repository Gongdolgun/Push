
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

//2024.01.05 이현중
//버프 자료형을 집어넣으면 그에 따른 엑터를 생성후 OnEffect를 호출
void UBuffComponent::AddBuff(TSubclassOf<ABuffInstance> BuffClass)
{
	if (!Owner.Get() || !BuffClass)
		return;

	FActorSpawnParameters param;
	param.Owner = Owner.Get();

	ABuffInstance* temp = Cast<ABuffInstance>(Owner->GetWorld()->SpawnActor(BuffClass,0,0, param));
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


