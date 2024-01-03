#include "Skill_Fireball_P.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASkill_Fireball_P::ASkill_Fireball_P()
{

}

void ASkill_Fireball_P::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASkill_Fireball_P::FOnBeginOverlap);
}

void ASkill_Fireball_P::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ASkill_Fireball_P::FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnDestroy();
}

void ASkill_Fireball_P::OnDestroy()
{
	Super::OnDestroy();

	// 231229 �̹���
	// ���� ��ƼŬ ��ȯ, No Collision, ���� Particle DeActive
	if (!!Explosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
	}

	Particle->SetActive(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}