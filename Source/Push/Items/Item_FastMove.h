#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Item_FastMove.generated.h"

UCLASS(Blueprintable)
class PUSH_API AItem_FastMove : public AItemBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void UseItem()  override;

private:
	UPROPERTY(EditAnywhere, Category = "BuffClass")
		TSubclassOf<class ABuffInstance> BuffClass;
};
