// Copyright Epic Games, Inc. All Rights Reserved.

#include "PushCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ResourceComponent.h"
#include "Components/MoveComponent.h"
#include "Components/BuffComponent.h"
#include "Components/ItemComponent.h"
#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Skill/Area/Area.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Global.h"
#include "Components/SkillComponent.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/WDG_EffectBase.h"
#include "Skill/SkillData.h"
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
    Helpers::CreateActorComponent<UResourceComponent>(this, &ResourceComponent, "ResourceComponent");
    Helpers::CreateActorComponent<USkillComponent>(this, &SkillComponent, "SkillComponent");
    Helpers::CreateActorComponent<UBuffComponent>(this, &BuffComponent, "BuffComponent");
    Helpers::CreateActorComponent<UItemComponent>(this, &ItemComponent, "ItemComponent");

    if(SkillComponent != nullptr)
    {
        SkillComponent->SetNetAddressable();
        SkillComponent->SetIsReplicated(true);
    }

    BodyColor = FLinearColor::MakeRandomColor();
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

    PlayerInputComponent->BindAction("KD", EInputEvent::IE_Pressed, ResourceComponent, &UResourceComponent::OnKillDeathUI);
    PlayerInputComponent->BindAction("KD", EInputEvent::IE_Released, ResourceComponent, &UResourceComponent::OffKillDeathUI);

}

void APushCharacter::Hit(AActor* InAttacker, const FHitData& InHitData)
{
    FVector direction = GetActorLocation() - InAttacker->GetActorLocation();
    direction = direction.GetSafeNormal();

    FVector launch = FVector(InHitData.xLaunchPower * direction.X, InHitData.xLaunchPower * direction.Y, InHitData.zLaunchPower);

    CLog::Log(InAttacker->GetActorLocation());
    CLog::Log(launch);

    if(ResourceComponent != nullptr)
    {
		ResourceComponent->AdjustHP(-InHitData.Damage);
    }

    if(launch.X + launch.Y + launch.Z > 0.0f)
    {
        LaunchServer(launch);
    }

    if(InHitData.Effect != nullptr)
    {
        UParticleSystem* particle = Cast<UParticleSystem>(InHitData.Effect);
        UNiagaraSystem* niagara = Cast<UNiagaraSystem>(InHitData.Effect);

        if(particle != nullptr)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, InHitData.Location, FRotator::ZeroRotator, InHitData.EffectScale);
        }

        if(niagara != nullptr)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), niagara, InHitData.Location, FRotator::ZeroRotator, InHitData.EffectScale);
        }
    }

    if(InHitData.Sound != nullptr)
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), InHitData.Sound, InHitData.Location);
    }
}

void APushCharacter::ChangeBodyColor_Server_Implementation(FLinearColor InColor)
{
    ChangeBodyColor_NMC_Implementation(InColor);
}

void APushCharacter::ChangeBodyColor_NMC_Implementation(FLinearColor InColor)
{
    if (HasAuthority() == true)
        return;

    Create_DynamicMaterial();
    Change_Color(InColor);
}

void APushCharacter::Create_DynamicMaterial()
{
    for (int32 i = 0; i < this->GetMesh()->GetMaterials().Num(); i++)
    {
        UMaterialInterface* material = this->GetMesh()->GetMaterials()[i];

        this->GetMesh()->SetMaterial(i, UMaterialInstanceDynamic::Create(material, this));
    }
}

void APushCharacter::Change_Color(FLinearColor InColor)
{
    CLog::Print("ChangeColor");
    for(UMaterialInterface* material : this->GetMesh()->GetMaterials())
    {
        UMaterialInstanceDynamic* MaterialDynamic = Cast<UMaterialInstanceDynamic>(material);

        if (MaterialDynamic)
        {
            MaterialDynamic->SetVectorParameterValue("BodyColor", InColor);
        }
    }

}

void APushCharacter::SetSpawnlocationRep_Implementation(FVector InVector)
{
    SetSpawnlocationNMC_Implementation(InVector);
}

void APushCharacter::SetSpawnlocationNMC_Implementation(FVector InVector)
{
	if(SkillComponent != nullptr)
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

void APushCharacter::SetBodyColor_Server_Implementation(FLinearColor InColor)
{
    SetBodyColor_NMC_Implementation(InColor);
}

void APushCharacter::SetBodyColor_NMC_Implementation(FLinearColor InColor)
{
    BodyColor = InColor;
}

void APushCharacter::Test()
{
    if (SkillComponent == nullptr)
        return;
    if (SkillComponent->curSkillData == nullptr)
        return;
    SkillComponent->curSkillData->Play(this);
}

//void APushCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//    DOREPLIFETIME(APushCharacter, BodyColor);
//}

void APushCharacter::PlayAnimMontageRep_Implementation(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate)
{
    PlayAnimMontageMC(InCharacter, InMontage, PlayRate);
}


void APushCharacter::PlayAnimMontageMC_Implementation(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate)
{
    if (InCharacter == nullptr || InMontage == nullptr)
        return;

    InCharacter->PlayAnimMontage(InMontage, PlayRate);
}


void APushCharacter::BeginPlay()
{
    Super::BeginPlay();

    ChangeBodyColor_Server_Implementation(BodyColor);
}

void APushCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

