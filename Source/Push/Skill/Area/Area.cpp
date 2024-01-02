#include "Area.h"
#include "Global.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

AArea::AArea()
{
	Helpers::CreateComponent(this, &Root, "Root", RootComponent);

	Helpers::CreateComponent(this, &Decal_Cursor, "Decal_Cursor", Root);

	Helpers::CreateComponent(this, &Particle, "Particle", Root);

	Decal_Cursor->SetVisibility(true);
	Decal_Cursor->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	

	Particle->bAutoActivate = false;
}

void AArea::BeginPlay()
{
	Super::BeginPlay();

	
}

void AArea::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bShowDecal)
	{
		TraceDecal();
		Decal_Cursor->SetWorldLocation(DecalLocation);
	}

}

void AArea::OnSkillPressed()
{
	Super::OnSkillPressed();

	bShowDecal = !bShowDecal;

	if (!bShowDecal)
	{
		Destroy();
	}
	
}

void AArea::TraceDecal()
{
	// 231229_���μ�
	// ī�޶� �ٶ󺸴� ���⿡ Decal_Cursor Spawn

	FVector start;
	FRotator PlayerViewRotation;
	APlayerController* controller = Cast<APlayerController>(Owner->GetController());

	if (controller)
		controller->GetPlayerViewPoint(start, PlayerViewRotation);

	FVector direction = PlayerViewRotation.Vector();
	FVector end = start + (direction * MaxDistance);

	FHitResult HitResult;
	TArray<AActor*> ignores;
	ignores.Add(Owner);

	UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), start, end, TraceType,false, ignores, DrawDebug, HitResult, true);

	// �ִ� �Ÿ� ���� Hit ������ ���ٸ�, �Ʒ��� �ѹ� �� ����
    if (HitResult.bBlockingHit)
    {
		// Decal�� ���� �İ� ���� -direction �������� ��ġ ����
		FVector DownStart = HitResult.ImpactPoint - (direction * 20.0f);
        FVector DownEnd = DownStart - FVector(0, 0, MaxDistance);

        FHitResult DownHitResult;
        UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), DownStart, DownEnd, TraceType,false, ignores, DrawDebug, DownHitResult, true);

        if (DownHitResult.bBlockingHit)
            DecalLocation = DownHitResult.ImpactPoint;

    	else
            DecalLocation = HitResult.ImpactPoint;
    }

    else
        DecalLocation = end;

    Decal_Cursor->SetWorldLocation(DecalLocation);
}

