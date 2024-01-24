#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Enums.h"
#include "StateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSH_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE bool GetAction() { return bInAction; }

public:
	// 24_01_12_���μ�
	void BeginAction();
	void EndAction();

	// State
	void SetIdleMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();

public:
	EStateType StateType;

	FStateTypeChanged OnStateTypeChanged;

private:
	void ChangeType(EStateType InType);


private:
	class ACharacter* Owner;

	bool bInAction = false;
};