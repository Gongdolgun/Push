#include "HUD/MainHUD.h"
#include "HUD/Resource.h"
#include "Widgets/WDG_EffectBase.h"
#include "Widgets/StoreUI.h"
#include "Widgets/KillDeathUI.h"
#include "Global.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	
	//AddEffectWidget();
}

void AMainHUD::DrawHUD()
{
	Super::DrawHUD();

}
//
//void AMainHUD::AddStoreUIWidget()
//{
//	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();
//	if (PlayerController.IsValid() && IsValid(StoreUIWidgetClass))
//	{
//		StoreUIWidget = CreateWidget<UStoreUI>(PlayerController.Get(), StoreUIWidgetClass);
//		StoreUIWidget->AddToViewport(); // Viewport에 등록
//	}
//}
//
//void AMainHUD::AddResourceWidget()
//{
//	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();
//	if (PlayerController.IsValid() && IsValid(ResourceWidgetClass))
//	{
//		ResourceWidget = CreateWidget<UResource>(PlayerController.Get(), ResourceWidgetClass);
//		ResourceWidget->AddToViewport(); // Viewport에 등록
//	}
//}
//
//void AMainHUD::AddEffectWidget()
//{
//	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();
//	if (PlayerController.IsValid() && IsValid(EffectWidgetClass))
//	{
//		EffectWidget = CreateWidget<UWDG_EffectBase>(PlayerController.Get(), EffectWidgetClass);
//		EffectWidget->AddToViewport(); // Viewport에 등록
//	}
//}
//
//void AMainHUD::AddKillDeathWidget()
//{
//	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();
//	if (PlayerController.IsValid() && IsValid(KillDeathWidgetClass))
//	{
//		KillDeathWidget = CreateWidget<UKillDeathUI>(PlayerController.Get(), KillDeathWidgetClass);
//		KillDeathWidget->AddToViewport(); // Viewport에 등록
//	}
//}

void AMainHUD::AddWidget()
{
	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();
	
	if (UserWidgetClasses.Num() == 0 || !PlayerController.IsValid())
		return;

	for (TPair<FString, TSubclassOf<UUserWidget>> widgetClass : UserWidgetClasses)
	{
		if(IsValid(widgetClass.Value))
		{
			UUserWidget* temp = CreateWidget<UUserWidget>(PlayerController.Get(), widgetClass.Value);
			temp->AddToViewport(); // Viewport에 등록
			UserWidgets.Add(widgetClass.Key, temp);
		}
	}
}
