#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUSH_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMoveComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
		void OnMoveForward(float InAxis);
	UFUNCTION(BlueprintCallable)
		void OnMoveRight(float InAxis);

	UFUNCTION(BlueprintCallable)
		void OnTurnAt(float Rate);

	UFUNCTION(BlueprintCallable)
		void OnLookUp(float Rate);
private:
	UPROPERTY(EditAnywhere, Category = "Move_Property")
		float SpeedX = 100;
	UPROPERTY(EditAnywhere, Category = "Move_Property")
		float SpeedY = 100;
	UPROPERTY(EditAnywhere, Category = "Move_Property")
		float SpeedPercent = 100;

	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float MouseSenceX = 100;
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float MouseSenceY = 100;
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float ViewMaxPitch = 90;
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float ViewMinPitch = -90;



private:
	TWeakObjectPtr<APawn> Owner;
};
