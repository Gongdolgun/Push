#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ring.generated.h"

UCLASS()
class PUSH_API ARing : public AActor
{
	GENERATED_BODY()
	
public:	
	ARing();

public:
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	//Collision을 담당하는 Capsule
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* RingCapsule;

	//자기장 생김새를 담당하는 Mesh
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* RingMesh;

	UPROPERTY(EditAnywhere)
		float RingDamage = 5.0f;

public:
	UFUNCTION(BlueprintCallable)
		void Shrink(float InRadius, float InTime);

	UFUNCTION(BlueprintCallable)
		void ChangeRadius();

	UFUNCTION()
		void Refresh();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// Base로 나누어 비율 계산하면 Capsule과 Mesh의 크기가 딱 맞습니다
	float Base = 50.0f;

	TArray<class APushCharacter*> OverlappedCharacters;
	FTimerHandle TimerHandle;

	float DeltaRadius = 0.0f;
	float TargetRadius;
};
