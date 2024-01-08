#include "Components/ShopComponent.h"
#include "GameFramework/Character.h"
#include "HUD/MainHUD.h"
#include "PlayerController/PushPlayerController.h"
#include "Widgets/StoreUI.h"

UShopComponent::UShopComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UShopComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
	PlayerController = Cast<APushPlayerController>(Owner->GetController());
	MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
}


void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UShopComponent::OpenStoreUI()
{
	if (Owner == nullptr || PlayerController == nullptr || MainHUD == nullptr)
		return;

	if(bOpen == false)
	{
		if(MainHUD->CheckWidget("Store") == true)
		{
			MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Visible);
			bOpen = true;
		}
	}

	else
	{
		if (MainHUD->CheckWidget("Store") == true)
		{
			MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);
			bOpen = false;
		}
	}
}
