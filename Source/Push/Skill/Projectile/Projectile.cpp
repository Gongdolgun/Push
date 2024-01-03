#include "Skill/Projectile/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
	ProjectileComponent = this->CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComponent");
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ProjectileComponent->InitialSpeed = 1000 * Speed;
	ProjectileComponent->ProjectileGravityScale = 1 * Gravity_Scale;
}
