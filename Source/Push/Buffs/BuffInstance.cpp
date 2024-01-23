#include "BuffInstance.h"

#include "Components/BuffComponent.h"
#include "Widgets/WDG_Buff.h"
#include "Global.h"
#include "Widgets/WDG_BuffBoard.h"

ABuffInstance::ABuffInstance()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = "WidgetBlueprint'/Game/BP/Widgets/BuffWidget/WDG_Buff.WDG_Buff_C'";

	WidgetClass = ConstructorHelpers::FClassFinder<UWDG_Buff>(*path).Class;
	bReplicates = true;
}

ABuffInstance::~ABuffInstance()
{
}

void ABuffInstance::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());

	if (!Owner.IsValid())
		return;

	APlayerController* controller = Cast<APlayerController>(Owner->GetController());
	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());
	if (!controller || !buffComponent)
		return;
	/*if (!controller->IsLocalController())
		return;*/
	if (HasAuthority())
		return;
	//버프 위젯 생성
	Widget = CreateWidget<UWDG_Buff>(controller, WidgetClass, "BuffWidget" + buffComponent->GetBuffCount()+1);
	Widget->SetBuffUI(UIImage, &PlayTime, &LifeTime);
	Widget->AddToViewport();

	buffComponent->Widget->AddBuff(Widget);

	OnEffect();
}

void ABuffInstance::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//2024.01.08 이현중
	//버프의 시간진행, 지속시간이 끝날시 제거
	PlayTime += DeltaSeconds;
	if (PlayTime > LifeTime)
	{
		if (!Owner.IsValid())
		{
			CLog::Print("buffInstanceError");
			return;
		}

		UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());
		if(!buffComponent)
		{
			CLog::Print("buffInstanceError");
			return;
		}
		buffComponent->RemoveBuff(this);
		OffEffect();

		if (!!Widget)
			Widget->RemoveFromParent();
		Destroy();
	}
}
