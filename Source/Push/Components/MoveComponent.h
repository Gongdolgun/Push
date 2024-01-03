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
	//2023.01.02 이현중
	// 플레이어 이동
	UFUNCTION(BlueprintCallable)
		void OnMoveForward(float InAxis);
	UFUNCTION(BlueprintCallable)
		void OnMoveRight(float InAxis);

	//2023.01.02 이현중
	// 플레이어 시야 변경
	UFUNCTION(BlueprintCallable)
		void OnTurnAt(float Rate);
	UFUNCTION(BlueprintCallable)
		void OnLookUp(float Rate);

public:
	FORCEINLINE void SetSpeedPercent(float speed) { SpeedPercent = speed; }
	FORCEINLINE float GetSpeedPercent() { return SpeedPercent; }

public:
	UFUNCTION()
		void UpdateSpeed();
private:

	UPROPERTY(EditAnywhere, Category = "Move_Property")
		float Speed = 600;
	UPROPERTY(EditAnywhere, Category = "Move_Property")
		float SpeedPercent = 100;

	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float MouseSenceX = 100;
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float MouseSenceY = 100;

	//2023.01.02 이현중
	//플레이어 최대 Pitch변경값
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float ViewMaxPitch = 90;
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float ViewMinPitch = -90;



private:
	TWeakObjectPtr<ACharacter> Owner;
};
