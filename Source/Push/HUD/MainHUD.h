#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/** UserWidget들을 통합하여 관리하는 HUD 클래스
 *  HUD는 GameMode에 등록된다.
 */

UCLASS()
class PUSH_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
	void AddStoreUIWidget();
	void AddResourceWidget();
	void AddEffectWidget();
	void AddKillDeathWidget();

	UPROPERTY(EditAnywhere, Category = "Store Widget")
	TSubclassOf<class UUserWidget> StoreUIWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Player Widget")
	TSubclassOf<class UUserWidget> ResourceWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Player Widget")
	TSubclassOf<class UUserWidget> EffectWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Player Widget")
	TSubclassOf<class UUserWidget> KillDeathWidgetClass;

	UPROPERTY()
	class UStoreUI* StoreUIWidget;

	UPROPERTY()
	class UResource* ResourceWidget;

	UPROPERTY()
	class UWDG_EffectBase* EffectWidget;

	UPROPERTY()
	class UKillDeathUI* KillDeathWidget;

protected:
	virtual void BeginPlay() override;
};