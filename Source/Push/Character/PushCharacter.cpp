// Copyright Epic Games, Inc. All Rights Reserved.

#include "PushCharacter.h"

#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ResourceComponent.h"
#include "Components/MoveComponent.h"
#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Global.h"
<<<<<<< Updated upstream
=======
#include "Components/SkillComponent.h"
#include "PlayerController/PushPlayerController.h"
>>>>>>> Stashed changes
#include "Widgets/WDG_EffectBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/PushPlayerController.h"

//////////////////////////////////////////////////////////////////////////
// APushCharacter

APushCharacter::APushCharacter()
{
    // 캡슐 사이즈 지정
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    //캐릭터 Movement설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
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
    Helpers::CreateActorComponent<UResourceComponent>(this, &ResourceComponent, "ResourceComponent");
<<<<<<< Updated upstream
=======
    Helpers::CreateActorComponent<USkillComponent>(this, &SkillComponent, "SkillComponent");
    Helpers::CreateActorComponent<UBuffComponent>(this, &BuffComponent, "BuffComponent");
    Helpers::CreateActorComponent<UItemComponent>(this, &ItemComponent, "ItemComponent");

    if (SkillComponent != nullptr)
    {
        SkillComponent->SetNetAddressable();
        SkillComponent->SetIsReplicated(true);
    }
>>>>>>> Stashed changes
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

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void APushCharacter::Hit(AActor* InAttacker, const FHitData& InHitData)
{
    FVector direction = GetActorLocation() - InAttacker->GetActorLocation();
    direction = direction.GetSafeNormal();

    FVector launch = FVector(InHitData.xLaunchPower * direction.X, InHitData.xLaunchPower * direction.Y, InHitData.zLaunchPower);

    if (ResourceComponent != nullptr)
    {
<<<<<<< Updated upstream
		ResourceComponent->AdjustHP(-InHitData.Damage);
        CLog::Log(InHitData.Damage);
    }

    if(InHitData.xLaunchValue + InHitData.yLaunchValue + InHitData.zLaunchValue > 0.0f)
    {
        LaunchCharacter(FVector(InHitData.xLaunchValue, InHitData.yLaunchValue, InHitData.zLaunchValue), false, false);
=======
        ResourceComponent->AdjustHP(-InHitData.Damage);
>>>>>>> Stashed changes
    }

    if (launch.X + launch.Y + launch.Z > 0.0f)
    {
        LaunchServer(launch);
    }


    if (InHitData.Effect != nullptr)
    {
        UParticleSystem* particle = Cast<UParticleSystem>(InHitData.Effect);
        UNiagaraSystem* niagara = Cast<UNiagaraSystem>(InHitData.Effect);

        if (particle != nullptr)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, InHitData.Location, FRotator::ZeroRotator, InHitData.EffectScale);
        }

        if (niagara != nullptr)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), niagara, InHitData.Location, FRotator::ZeroRotator, InHitData.EffectScale);
        }
    }

    if (InHitData.Sound != nullptr)
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), InHitData.Sound, InHitData.Location);
    }
}

void APushCharacter::ServerChangeMaterial_Implementation(ACharacter* Character, FLinearColor NewColor)
{
    if (Character != nullptr)
    {
        MulticastChangeMaterial(Character, NewColor);
    }
}

void APushCharacter::MulticastChangeMaterial_Implementation(ACharacter* Character, FLinearColor NewColor)
{
<<<<<<< Updated upstream
    if (Character != nullptr)
    {
        CLog::Print("MultiCast");

        Create_DynamicMaterial(Character);
        Change_Color(Character, NewColor);
    }
=======
    if (SkillComponent != nullptr)
        SkillComponent->SpawnLocation = InVector;
}

void APushCharacter::LaunchServer_Implementation(FVector InLaunch)
{
    LaunchNMC_Implementation(InLaunch);
}

void APushCharacter::LaunchNMC_Implementation(FVector InLaunch)
{
    LaunchCharacter(InLaunch, false, false);
}

void APushCharacter::Create_DynamicMaterial(ACharacter* InCharacter)
{
    for (int32 i = 0; i < InCharacter->GetMesh()->GetMaterials().Num(); i++)
    {
        UMaterialInterface* material = InCharacter->GetMesh()->GetMaterials()[i];

        InCharacter->GetMesh()->SetMaterial(i, UMaterialInstanceDynamic::Create(material, InCharacter));
    }
}

void APushCharacter::Change_Color(FLinearColor InColor)
{
    for (UMaterialInterface* material : this->GetMesh()->GetMaterials())
    {
        UMaterialInstanceDynamic* MaterialDynamic = Cast<UMaterialInstanceDynamic>(material);

        if (MaterialDynamic)
        {
            MaterialDynamic->SetVectorParameterValue("BodyColor", InColor);
        }
    }

}

void APushCharacter::Test()
{
    if (SkillComponent == nullptr)
        return;

    if (SkillComponent->curSkillData == nullptr)
        return;

    SkillComponent->curSkillData->Play(this);
}

void APushCharacter::PlayAnimMontageRep_Implementation(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate)
{
    PlayAnimMontageMC(InCharacter, InMontage, PlayRate);
}


void APushCharacter::PlayAnimMontageMC_Implementation(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate)
{
    if (InCharacter == nullptr || InMontage == nullptr)
        return;

    InCharacter->PlayAnimMontage(InMontage, PlayRate);
>>>>>>> Stashed changes
}


void APushCharacter::BeginPlay()
{
    Super::BeginPlay();

<<<<<<< Updated upstream
    //ServerChangeMaterial_Implementation(this, FLinearColor::MakeRandomColor());
=======
>>>>>>> Stashed changes

}

void APushCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}
<<<<<<< Updated upstream

void APushCharacter::Create_DynamicMaterial(ACharacter* InCharacter)
{
    for (int32 i = 0; i < InCharacter->GetMesh()->GetMaterials().Num(); i++)
    {
        UMaterialInterface* material = InCharacter->GetMesh()->GetMaterials()[i];
    
        InCharacter->GetMesh()->SetMaterial(i, UMaterialInstanceDynamic::Create(material, InCharacter));
    }
}

void APushCharacter::Change_Color(ACharacter* InCharacter, FLinearColor InColor)
{
    for (UMaterialInterface* material : InCharacter->GetMesh()->GetMaterials())
    {
        UMaterialInstanceDynamic* MaterialDynamic = Cast<UMaterialInstanceDynamic>(material);

        if (MaterialDynamic)
        {
            MaterialDynamic->SetVectorParameterValue("BodyColor", InColor);
        }
    }
}
=======
>>>>>>> Stashed changes
