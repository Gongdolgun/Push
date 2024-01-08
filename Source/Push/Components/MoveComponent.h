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
	//2023.01.02 ������
	// �÷��̾� �̵�
	UFUNCTION(BlueprintCallable)
		void OnMoveForward(float InAxis);
	UFUNCTION(BlueprintCallable)
		void OnMoveRight(float InAxis);

	//2023.01.02 ������
	// �÷��̾� �þ� ����
	UFUNCTION(BlueprintCallable)
		void OnTurnAt(float Rate);
	UFUNCTION(BlueprintCallable)
		void OnLookUp(float Rate);

public:
	FORCEINLINE void SetSpeedPercent(float speed) { SpeedPercent = speed; }
	FORCEINLINE float GetSpeedPercent() { return SpeedPercent; }

public:
	UFUNCTION(BlueprintCallable)
		void UpdateSpeed();

private:
	UPROPERTY(EditAnywhere,Category = "Move_Property")
		float Speed = 600;
	UPROPERTY(EditAnywhere,Category = "Move_Property")
		float SpeedPercent = 100;

	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float MouseSenceX = 45.0f;
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float MouseSenceY = 45.0f;

	//2023.01.02 ������
	//�÷��̾� �ִ� Pitch���氪
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float ViewMaxPitch = 90;
	UPROPERTY(EditAnywhere, Category = "Mouse_Property")
		float ViewMinPitch = -90;



private:
	TWeakObjectPtr<ACharacter> Owner;
};