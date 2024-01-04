#include "Push/HUD/MainHUD.h"
#include "Push/HUD/Resource.h"
#include "Push/Widgets/WDG_EffectBase.h"
#include "Global.h"

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();

    AddResourceWidget();
    AddEffectWidget();
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
        ResourceWidget->AddToViewport(); // Viewport에 등록
    }
}

void AMainHUD::AddEffectWidget()
{
    TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();
    if (PlayerController.IsValid() && IsValid(EffectWidgetClass))
    {
        EffectWidget = CreateWidget<UWDG_EffectBase>(PlayerController.Get(), EffectWidgetClass);
        EffectWidget->AddToViewport(); // Viewport에 등록
    }
}
