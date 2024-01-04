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
	void AddResourceWidget();

	UPROPERTY(EditAnywhere, Category = "Player Resource")
		TSubclassOf<class UUserWidget> ResourceWidgetClass;

	UPROPERTY()
		class UResource* ResourceWidget;
	//TObjectPtr<class UResource> ResourceWidget;

protected:
	virtual void BeginPlay() override;
};