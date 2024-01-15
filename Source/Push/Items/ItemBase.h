#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/Structures.h"
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
	virtual void UseItem() PURE_VIRTUAL(AItemBase::Use, ;);

public:
	TWeakObjectPtr<ACharacter> Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FProduct Product;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* ItemImage;*/
};