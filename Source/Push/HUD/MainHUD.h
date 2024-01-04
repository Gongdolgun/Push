#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/** UserWidget���� �����Ͽ� �����ϴ� HUD Ŭ����
 *  HUD�� GameMode�� ��ϵȴ�.
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