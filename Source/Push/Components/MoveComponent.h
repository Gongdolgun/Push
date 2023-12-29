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
		void MoveForward(float InAxis);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float InAxis);

private:
	UPROPERTY(EditAnywhere, Category = "Property")
		float SpeedX;

	UPROPERTY(EditAnywhere, Category = "Property")
		float SpeedY;
	UPROPERTY(EditAnywhere, Category = "Property")
		float SpeedPercent;
private:
	TWeakObjectPtr<ACharacter> Owner;
};
