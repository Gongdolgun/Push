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

	UPROPERTY(EditAnywhere, Category = "Player Resource")
		TSubclassOf<class UUserWidget> ResourceWidgetClass;

	UPROPERTY()
		class UResource* ResourceWidget;
	//TObjectPtr<class UResource> ResourceWidget;

protected:
	virtual void BeginPlay() override;
};