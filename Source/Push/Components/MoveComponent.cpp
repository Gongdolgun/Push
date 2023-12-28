#include "MoveComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	//Owner = GetOwner();
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::MoveForward(float InAxis)
{
	if (!IsValid(Owner.Get()))
		return;

	FVector direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));

	Owner->AddMovementInput(direction, (SpeedX * SpeedPercent));

}

void UMoveComponent::MoveRight(float InAxis)
{
	if (!IsValid(Owner.Get()))
		return;

	FVector direction = UKismetMathLibrary::GetRightVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));

	Owner->AddMovementInput(direction, (SpeedY * SpeedPercent));

}

