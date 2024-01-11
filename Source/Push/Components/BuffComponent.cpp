
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


//2024.01.05 이현중
//버프 자료형을 집어넣으면 그에 따른 엑터를 생성후 OnEffect를 발생 <- 2024.01.09 기존 클래스생성에서 엑터생성으로 변경
// 2024.01.10 기존 클라이언트에서만 할당하던 Add를 서버가 사용하도록 설정
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


