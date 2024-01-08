#include "Push/HUD/MainHUD.h"
#include "Push/HUD/Resource.h"
#include "Global.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	AddResourceWidget();
}

void AMainHUD::DrawHUD()
{
	Super::DrawHUD();

}

void AMainHUD::AddResourceWidget()
{
	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();
	if (PlayerController.IsValid() && IsValid(ResourceWidgetClass))
	{
		ResourceWidget = CreateWidget<UResource>(PlayerController.Get(), ResourceWidgetClass);
		ResourceWidget->AddToViewport(); // Viewport¿¡ µî·Ï
	}
}
