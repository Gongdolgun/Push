#include "Skill/Projectile/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Global.h"

AProjectile::AProjectile()
{
	Helpers::CreateComponent(this, &Root, "Root");
	Helpers::CreateComponent(this, &Mesh, "Mesh", Root);
	Helpers::CreateComponent(this, &Collision, "Collision", Root);

	Helpers::CreateActorComponent(this, &ProjectileComponent, "ProjectileComponent");
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Datas.CanRotate == true)
	{
		// 231229 �̹���
		// ���� ���� Projectile �ٽ��ڵ�
		if (!!Owner && !!Owner->GetController())
		{
			rotation = FRotator(GetActorRotation().Pitch, Owner->GetController()->GetControlRotation().Yaw, GetActorRotation().Roll);
			velocity = UKismetMathLibrary::GetForwardVector(rotation) * ProjectileComponent->InitialSpeed;

			ProjectileComponent->Velocity = UKismetMathLibrary::VInterpTo(ProjectileComponent->Velocity, velocity, DeltaSeconds, Datas.InterpSpeed);
			SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), rotation, DeltaSeconds, Datas.InterpSpeed));
		}
	}
}

void AProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 231229 �̹���
	// ���ǵ�, �߷°� �ʱ�ȭ
	ProjectileComponent->InitialSpeed = 1000 * Datas.Speed;
	ProjectileComponent->ProjectileGravityScale = 1 * Datas.Gravity_Scale;
}
