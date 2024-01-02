#include "MoveComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Global.h"

UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Owner = Cast<APawn>(GetOwner());
}


void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::OnMoveForward(float InAxis)
{
	if (!IsValid(Owner.Get()))
		return;
	FVector direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));
	
	Owner->AddMovementInput(direction, ((SpeedX * InAxis) * SpeedPercent));
}

void UMoveComponent::OnMoveRight(float InAxis)
{
	if (!IsValid(Owner.Get()))
	{
		FRotator rotate = Owner->GetActorRotation();
		rotate.Yaw = rotate.Yaw + SpeedY * InAxis;
		Owner->SetActorRotation(rotate);
		

		return;
	}
	FVector direction = UKismetMathLibrary::GetRightVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));

	Owner->AddMovementInput(direction, ((SpeedY * InAxis) * SpeedPercent));

}
