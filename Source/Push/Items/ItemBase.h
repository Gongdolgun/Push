#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "ItemBase.generated.h"

UCLASS()
class PUSH_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void UseItem() {};
	
protected:
	TWeakObjectPtr<ACharacter> Owner;
	UPROPERTY(EditAnywhere)
		FString ItemName;
};

