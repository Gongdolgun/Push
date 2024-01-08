#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PointDecal.generated.h"

UCLASS(Blueprintable)
class PUSH_API APointDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	APointDecal();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE class UDecalComponent* GetDecalComponent() { return PointDecal; }

	void SetDecalTime(float InDecalTime);

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Decal")
		class UDecalComponent* PointDecal;

private:
	class UMaterialInstanceDynamic* Dynamic;

	UPROPERTY()
		float DecalTime;

	float Radius = 0.0f;
	float MaxRadius = 0.5f;
	float InterpSpeed = 0.0f;

	float CurrentTime;

	UPROPERTY(EditAnywhere)
		float Correction;
	
	
};
