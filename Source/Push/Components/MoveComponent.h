#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

private:
	UPROPERTY(EditAnywhere, Category = "Property")
		float SpeedX = 100;

	UPROPERTY(EditAnywhere, Category = "Property")
		float SpeedY = 100;
	UPROPERTY(EditAnywhere, Category = "Property")
		float SpeedPercent = 100;

private:
	TWeakObjectPtr<APawn> Owner;
};
