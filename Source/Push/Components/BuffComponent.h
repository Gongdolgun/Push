#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Buffs/BuffInstance.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSH_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void AddBuff(TSubclassOf<UBuffInstance> BuffClass);


private:
	class ACharacter* Owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	meta = (AllowPrivateAccess))
		TArray<UBuffInstance*> Buffs;
};
