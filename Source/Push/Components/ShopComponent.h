#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSH_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShopComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	ACharacter* Owner;
	class APushPlayerController* PlayerController;
	class AMainHUD* MainHUD;

	bool bOpen = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<class USkillData>> SkillDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UMainUI* MainUI;

public:
	UFUNCTION(BlueprintCallable)
		void OpenStoreUI();
};
