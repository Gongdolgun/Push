#pragma once

#include "CoreMinimal.h"
#include "Buffs/BuffInstance.h"
#include "BuffInstance_Freezing.generated.h"

UCLASS()
class PUSH_API ABuffInstance_Freezing : public ABuffInstance
{
	GENERATED_BODY()
public:
	virtual void OnEffect() override;
	virtual void OffEffect() override;

	UFUNCTION(Reliable, Server)
		void Test_S();
	UFUNCTION(NetMulticast, Reliable)
		void Test_N();
private:
	// class UAnimInstance_PushCharacter* AnimInstance;
};
