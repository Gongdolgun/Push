#include "Components/StateComponent.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
}

void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UStateComponent::BeginAction()
{
	bInAction = true;
	SetActionMode();
}

void UStateComponent::EndAction()
{
	bInAction = false;
	SetIdleMode();
}

void UStateComponent::SetIdleMode()
{
	ChangeType(EStateType::ES_Idle);
}

void UStateComponent::SetActionMode()
{
	ChangeType(EStateType::ES_Action);
}

void UStateComponent::SetHittedMode()
{
	ChangeType(EStateType::ES_Hitted);
}

void UStateComponent::SetDeadMode()
{
	ChangeType(EStateType::ES_Dead);
}

void UStateComponent::ChangeType(EStateType InType)
{
	EStateType prevType = StateType;
	StateType = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevType, StateType);
}

