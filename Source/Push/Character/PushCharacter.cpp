#include "PushCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/Area/Area.h"
#include "Skill/Area/AreaSkills/Skill_Meteor_A.h"


//////////////////////////////////////////////////////////////////////////
// APushCharacter

APushCharacter::APushCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}

//////////////////////////////////////////////////////////////////////////
// Input

void APushCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//// Set up gameplay key bindings
	//check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APushCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APushCharacter::MoveRight);

	//// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	//// "turn" handles devices that provide an absolute delta, such as a mouse.
	//// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APushCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APushCharacter::LookUpAtRate);

	//// handle touch devices
	//PlayerInputComponent->BindTouch(IE_Pressed, this, &APushCharacter::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &APushCharacter::TouchStopped);

	//// VR headset functionality
	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &APushCharacter::OnResetVR);
}

void APushCharacter::NumberPressed()
{
	if (!SkillActor.IsValid())
	{
		FTransform SkillTransform;
		SkillTransform.SetLocation(FVector(GetActorLocation()));
		SkillTransform.SetRotation(FQuat(FRotator(0, 0, 0)));
		SkillTransform.SetScale3D(FVector(1, 1, 1));

		FActorSpawnParameters param;
		param.Owner = this;

		SkillActor = MakeWeakObjectPtr(GetWorld()->SpawnActor<ASkill_Meteor_A>(SubclassSkill, SkillTransform, param));
		SkillActor->OnSkillPressed();
	}

	else
	{
		SkillActor->OnSkillPressed();
	}
	
}

void APushCharacter::OnSkillClicked()
{
	if (SkillActor.IsValid())
	{
		SkillActor->OnSkillClicked();
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


void APushCharacter::OnResetVR()
{
	// If Push is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Push.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void APushCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void APushCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void APushCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APushCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APushCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APushCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
