#include "MoveComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Global.h"
#include "GameFramework/CharacterMovementComponent.h"

UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());

	//2023.12.29 이현중
	//view허용값 설정
	APlayerController* playerController = Cast<APlayerController>(Owner->GetController());

	if (playerController)
	{
		playerController->PlayerCameraManager->ViewPitchMax = ViewMaxPitch;
		playerController->PlayerCameraManager->ViewPitchMin = ViewMinPitch;
		UpdateSpeed();
	}
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::OnMoveForward(float InAxis)
{
	if (!IsValid(Owner.Get()))
		return;
	//FVector direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));
	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	//2023.12.28 이현중
	// 앞,뒤 이동
	Owner->AddMovementInput(direction, InAxis);
}

void UMoveComponent::OnMoveRight(float InAxis)
{
	//2023.12.28 이현중
	// 좌,우 이동
	//FVector direction = UKismetMathLibrary::GetRightVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));
	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	Owner->AddMovementInput(direction, InAxis);

}

//2023.12.29 이현중
// OnTurnAt, OnLookUp 마우스에 따른 시점 이동
void UMoveComponent::OnTurnAt(float Rate)
{
	Owner->AddControllerYawInput(Rate * MouseSenceX * GetWorld()->GetDeltaSeconds());
}

void UMoveComponent::OnLookUp(float Rate)
{
	Owner->AddControllerPitchInput(Rate * MouseSenceY * GetWorld()->GetDeltaSeconds());
}

void UMoveComponent::UpdateSpeed()
{
	UCharacterMovementComponent* movementComponent = Helpers::GetComponent<UCharacterMovementComponent>(Owner.Get());


	movementComponent->MaxWalkSpeed = Speed * (SpeedPercent / 100);
}

