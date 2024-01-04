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

	virtual void Use()  override;

private:
	UPROPERTY(EditAnywhere, Category = "Property",
		meta= (ClampMin = "0", ClampMax = "100.0", UIMin = "0", UIMax = "100.0"))
		float PlusSpeedPercent = 20.0f;
};
