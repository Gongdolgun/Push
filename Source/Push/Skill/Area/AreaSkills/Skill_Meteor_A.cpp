#include "Skill/Area/AreaSkills/Skill_Meteor_A.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "Components/DecalComponent.h"
#include "Components/SkillComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Skill/SkillData.h"
#include "Skill/Area/PointDecal.h"

ASkill_Meteor_A::ASkill_Meteor_A()
{
    bReplicates = true;

    Helpers::CreateComponent(this, &SphereComponent, "Collision", Root);
    SphereComponent->SetSphereRadius(128.0f);

    Helpers::CreateActorComponent(this, &ProjectileComponent, "ProjectileComponent");
    ProjectileComponent->InitialSpeed = 1000.0f;
    ProjectileComponent->ProjectileGravityScale = 0.0f;

}

void ASkill_Meteor_A::BeginPlay()
{

    Super::BeginPlay();

    USkillComponent* skillComponent = Helpers::GetComponent<USkillComponent>(Owner);
    Particle->SetVisibility(true);
    Particle->Activate(true);
    ProjectileComponent->Activate(true);

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ASkill_Meteor_A::OnComponentBeginOverlap);

    OnSkillClicked();
}

void ASkill_Meteor_A::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void ASkill_Meteor_A::OnSkillPressed()
{
    Super::OnSkillPressed();


}

void ASkill_Meteor_A::OnSkillClicked()
{
    Super::OnSkillClicked();

    USkillComponent* skillComponent = Helpers::GetComponent<USkillComponent>(Owner);

    if (skillComponent == nullptr)
    {
        return;
    }

    FVector Meteor_Location = skillComponent->SpawnLocation - skillComponent->curSkillData->RelativeLocation;

    // Meteor Direction
    FVector direction = (skillComponent->SpawnLocation - Meteor_Location).GetSafeNormal();
    ProjectileComponent->Velocity = ProjectileComponent->InitialSpeed * (-direction);
    //Projectile_Server_Implementation(direction);


    FHitResult HitResult;
    TArray<AActor*> ignores;
    ignores.Add(Owner);

    // Meteor Trace
    UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), skillComponent->SpawnLocation, Meteor_Location,
        ETraceTypeQuery::TraceTypeQuery1, false, ignores, EDrawDebugTrace::ForDuration, HitResult, true);



    // 떨어지는 시간 구하기
    float falling_Distance = FVector::Dist(skillComponent->SpawnLocation, Meteor_Location);
    float falling_Speed = ProjectileComponent->Velocity.Size();

    float fallingTime = falling_Distance / falling_Speed;

    // Point Decal Spawn
    FTransform decalTransform;
    FVector CollisionLocation = Meteor_Location;
    decalTransform.SetLocation(CollisionLocation);

    APointDecal* DeferredDecal = Cast<APointDecal>(
        Owner->GetWorld()->SpawnActorDeferred<APointDecal>(Decal_Class, decalTransform));

    if (DeferredDecal != nullptr)
    {
        DeferredDecal->SetDecalTime(fallingTime);
        UGameplayStatics::FinishSpawningActor(DeferredDecal, decalTransform);
    }



}

void ASkill_Meteor_A::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    IDamageable* character = Cast<IDamageable>(OtherActor);
    USkillComponent* skillComponent = Helpers::GetComponent<USkillComponent>(Owner);

    if (skillComponent == nullptr)
    {
        return;
    }

    FVector CollisionLocation = skillComponent->SpawnLocation - skillComponent->curSkillData->RelativeLocation;

    OnDestroy(CollisionLocation);

    // 땅에 닿을 때, 캐릭터가 아니여야함
    if (!Cast<APawn>(OtherActor))
    {
        FVector start = CollisionLocation;
        FVector end = CollisionLocation;
        float radius = 150.0f;

        //CLog::Print(start);

        // 데미지를 줄 Pawn만 추적
        FHitResult Particle_HitResult;
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
        ObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

        TArray<AActor*> ignores;
        ignores.Add(Owner);

        UKismetSystemLibrary::SphereTraceSingleForObjects(Owner->GetWorld(), start, end, radius, ObjectType,
            false, ignores, DrawDebug_Particle, Particle_HitResult, true);

        if (Particle_HitResult.bBlockingHit)
        {
            // TODO : Hit Interface 데미지 처리
            if (character == nullptr)
                return;

            CLog::Print("Meteor Hit");
            character->Hit(this, HitData);

        }
    }


}

void ASkill_Meteor_A::OnDestroy(FVector InLocation)
{
    Super::OnDestroy(InLocation);

    // 폭발 파티클 소환
    if (Explosion)
    {
        FTransform explosionTramsform;
        explosionTramsform.SetLocation(InLocation);
        explosionTramsform.SetScale3D(ExplosionScale);
        UGameplayStatics::SpawnEmitterAtLocation(Owner->GetWorld(), Explosion, explosionTramsform);

        Particle->SetIsReplicated(true);
        Particle->SetActive(false);
    }

}