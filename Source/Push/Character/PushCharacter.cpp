// Copyright Epic Games, Inc. All Rights Reserved.

#include "PushCharacter.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ResourceComponent.h"
#include "Components/MoveComponent.h"

#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Skill/Area/Area.h"
#include "Global.h"

//////////////////////////////////////////////////////////////////////////
// APushCharacter

APushCharacter::APushCharacter()
{
	// ĸ�� ������ ����
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//ĳ���� Movement����
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 	
	CameraBoom->bUsePawnControlRotation = true; 

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

	//Component
	Helpers::CreateActorComponent<UMoveComponent>(this, &MoveComponent, "MoveComponent");
	Helpers::CreateActorComponent<UResourceComponent>(this, &ResorceComponent, "ResourceComponent");
}


// Input
void APushCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", MoveComponent, &UMoveComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", MoveComponent, &UMoveComponent::OnMoveRight);

	PlayerInputComponent->BindAxis("Turn", MoveComponent, &UMoveComponent::OnTurnAt);
	PlayerInputComponent->BindAxis("LookUp", MoveComponent, &UMoveComponent::OnLookUp);
}

void APushCharacter::NumberPressed()
{
	FTransform SkillTransform;
	SkillTransform.SetLocation(FVector(GetActorLocation()));
	SkillTransform.SetRotation(FQuat(FRotator(0, 0, 0)));
	SkillTransform.SetScale3D(FVector(1, 1, 1));

	FActorSpawnParameters param;
	param.Owner = this;

	SkillActor = GetWorld()->SpawnActor<AArea>(SkillClass, SkillTransform, param);

	if (SkillActor)
	{
		SkillActor->SkillPressed();
	}
}

void APushCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APushCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}


