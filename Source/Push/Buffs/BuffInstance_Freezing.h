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

	UFUNCTION(Server,Reliable)
		void OnSnapshot_Server();
	UFUNCTION(NetMulticast, Reliable)
		void OnSnapshot_NMC();

	UFUNCTION(Server, Reliable)
		void OffSnapshot_Server();
	UFUNCTION(NetMulticast, Reliable)
		void OffSnapshot_NMC();


private:
	 class UMoveComponent* MoveComponent;
	 class UAnimInstance_PushCharacter* AnimInstance;
};
