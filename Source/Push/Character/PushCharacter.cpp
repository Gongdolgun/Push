// Copyright Epic Games, Inc. All Rights Reserved.

#include "PushCharacter.h"

#include <GameFramework/PlayerStart.h>

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ResourceComponent.h"
#include "Components/MoveComponent.h"
#include "Components/BuffComponent.h"
#include "Components/ItemComponent.h"
#include "Components/ShopComponent.h"
#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Skill/Area/Area.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Global.h"
#include "Components/SkillComponent.h"
#include "Components/StateComponent.h"
#include "Components/WidgetComponent.h"
#include "GameInstance/PushGameInstance.h"
#include "GameMode/PushGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/WDG_EffectBase.h"
#include "Widgets/SkillSlots.h"
#include "Skill/SkillData.h"
#include "PlayerController/PushPlayerController.h"
#include "Widgets/PlayerNameTag.h"
#include "Widgets/SkillSlots.h"

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
    Helpers::CreateActorComponent<UShopComponent>(this, &ShopComponent, "ShopComponent");
    Helpers::CreateActorComponent<UStateComponent>(this, &StateComponent, "StateComponent");
    Helpers::CreateActorComponent<UWidgetComponent>(this, &WidgetComponent, "PlayerNameTag");


	/*if (ResourceComponent != nullptr)
	{
		ResourceComponent->SetNetAddressable();
		ResourceComponent->SetIsReplicated(true);
	}*/

    if(SkillComponent != nullptr)
    {
        SkillComponent->SetNetAddressable();
        SkillComponent->SetIsReplicated(true);
    }
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

    /*PlayerInputComponent->BindAction<TDelegate<void(int)>>("Skill1", EInputEvent::IE_Pressed, SkillSlots, &USkillSlots::UseSkill, 0);
    PlayerInputComponent->BindAction<TDelegate<void(int)>>("Skill2", EInputEvent::IE_Pressed, SkillSlots, &USkillSlots::UseSkill, 1);
    PlayerInputComponent->BindAction<TDelegate<void(int)>>("Skill3", EInputEvent::IE_Pressed, SkillSlots, &USkillSlots::UseSkill, 2);
    PlayerInputComponent->BindAction<TDelegate<void(int)>>("Skill4", EInputEvent::IE_Pressed, SkillSlots, &USkillSlots::UseSkill, 3);*/
}

void APushCharacter::Hit(AActor* InAttacker, const FHitData& InHitData)
{
    // 킬 로그 출력
    ResourceComponent->ShowKillLog(InAttacker, this);
    
    FVector direction = GetActorLocation() - InAttacker->GetActorLocation();
    direction = direction.GetSafeNormal();

    FVector launch = FVector(InHitData.xLaunchPower * direction.X, InHitData.xLaunchPower * direction.Y, InHitData.zLaunchPower);

    if(ResourceComponent != nullptr)
    {
        if (ResourceComponent->GetHP() <= 0.0f)
        {
            return;
        }

        if (ResourceComponent->GetHP() - InHitData.Damage <= 0)
        {
            ResourceComponent->SetHP_Server(0.0f);
            Ragdoll();
            StateComponent->SetDeadMode();
        }
        else
        {
            ResourceComponent->AdjustHP_Server(-InHitData.Damage);
        }
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

void APushCharacter::SetLocation_Implementation(FVector InLocation)
{
    SetActorLocation(InLocation);
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
    //CLog::Print("ChangeColor");
    for(UMaterialInterface* material : this->GetMesh()->GetMaterials())
    {
        UMaterialInstanceDynamic* MaterialDynamic = Cast<UMaterialInstanceDynamic>(material);

        if (MaterialDynamic)
        {
            MaterialDynamic->SetVectorParameterValue("BodyColor", InColor);
        }
    }

}

void APushCharacter::LaunchServer_Implementation(FVector InLaunch)
{
    LaunchNMC_Implementation(InLaunch);
}

void APushCharacter::LaunchNMC_Implementation(FVector InLaunch)
{
    LaunchCharacter(InLaunch, false, false);
}

void APushCharacter::Test()
{
    if (SkillComponent == nullptr)
        return;
    if (SkillComponent->curSkillData == nullptr)
        return;
    SkillComponent->curSkillData->Play(this);
}

void APushCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APushCharacter, BodyColor);
    DOREPLIFETIME(APushCharacter, CustomPlayerName);
}

void APushCharacter::SetUpLocalName()
{
    if (IsLocallyControlled())
    {
        UPushGameInstance* gameInstance = Cast<UPushGameInstance>(GetGameInstance());
        if (gameInstance)
			SetPlayerNameServer(gameInstance->GetPlayerName());
    }
}

void APushCharacter::OnRep_CustomPlayerName()
{
    UPlayerNameTag* playerTag = Cast<UPlayerNameTag>(WidgetComponent->GetWidget());

    if (playerTag)
		playerTag->SetPlayerName(CustomPlayerName);

}

void APushCharacter::Ragdoll()
{
    if (GetCapsuleComponent()->GetCollisionEnabled() == ECollisionEnabled::NoCollision) return;

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    GetMesh()->SetCollisionProfileName("Ragdoll");
    GetMesh()->SetSimulatePhysics(true);

    FVector ImpulseDirection = GetActorRotation().Vector() * -1.0f;
    ImpulseDirection.Normalize();

    //충돌 세기
    float ImpulseStrength = 5000.0f;

    FVector FinalImpulse = ImpulseDirection * ImpulseStrength;

    //GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);
    GetMesh()->AddImpulseToAllBodiesBelow(FinalImpulse, NAME_None);


    ////** 죽은 후 위치 랜덤으로 스폰
    //FTimerHandle TimerHandle;
    //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APushCharacter::SetSpawnPoint, 1.5f, false, 1.5f);
}

void APushCharacter::SetSpawnPoint()
{
    TArray<AActor*> temp;
    UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), temp);

    TArray<APlayerStart*> PlayerStarts;
    for (auto Start : temp)
    {
        APlayerStart* startLoc = Cast<APlayerStart>(Start);
        if (IsValid(startLoc))
        {
        	PlayerStarts.Add(startLoc);
        }
    }
    if (PlayerStarts.Num() > 0)
    {
        TWeakObjectPtr<APlayerStart> ChosenPlayerStart = PlayerStarts[FMath::RandRange(0, PlayerStarts.Num() - 1)];
        SetActorLocationAndRotation(ChosenPlayerStart->GetActorLocation(), ChosenPlayerStart->GetActorRotation());
    }

    // 분리된 capsule 다시 붙이기
    GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    // 기본 상태로 되돌림
    StateComponent->SetIdleMode();
}

void APushCharacter::ShowKillLog(AActor* InAttacker)
{
    if (!InAttacker || !InAttacker->GetOwner()) return;

    APushCharacter* Attacker = Cast<APushCharacter>(InAttacker->GetOwner());
    FString AttackerName = Attacker->CustomPlayerName;

    if (Attacker)
    {
        CLog::Print(AttackerName);

        TArray<AActor*> PlayerControllers;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APushPlayerController::StaticClass(), PlayerControllers);

        for (AActor* Actor : PlayerControllers)
        {
            APushPlayerController* PlayerController = Cast<APushPlayerController>(Actor);
            if (PlayerController)
            {
                PlayerController->ShowKillLog_NMC(AttackerName, CustomPlayerName);
            }
        }
    }
}

void APushCharacter::SetPlayerNameServer_Implementation(const FString& NewPlayerName)
{
    CustomPlayerName = NewPlayerName;
}

void APushCharacter::BeginPlay()
{
    Super::BeginPlay();

    Create_DynamicMaterial();
    Change_Color(BodyColor);

    SetUpLocalName();
}

void APushCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);


}
