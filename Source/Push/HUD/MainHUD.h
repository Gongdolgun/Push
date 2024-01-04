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
	void AddResourceWidget();
	void AddEffectWidget();

	UPROPERTY(EditAnywhere, Category = "Player Widget")
		TSubclassOf<class UUserWidget> ResourceWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Player Widget")
		TSubclassOf<class UUserWidget> EffectWidgetClass;

	UPROPERTY()
		class UResource* ResourceWidget;

	UPROPERTY()
		class UWDG_EffectBase* EffectWidget;

protected:
	virtual void BeginPlay() override;
};