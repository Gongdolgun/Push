#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSH_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UResourceComponent();

	FORCEINLINE float GetHP() { return HP; }
	FORCEINLINE void SetHP(float hp) { HP = hp; }
	
	
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = "Property")
		float HP = 100.0f;
	UPROPERTY(EditAnywhere,  Category = "Property")
		float MaxHP = 100.0f;

};
