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

void AArea::OnSkillClicked()
{
	Super::OnSkillClicked();

	
}

void AArea::TraceDecal()
{
	// 231229_문인수
	// 카메라가 바라보는 방향에 Decal_Cursor Spawn

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

	UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), start, end, TraceType, false, ignores, DrawDebug_Decal, HitResult, true);

	// 최대 거리 전에 Hit 판정이 난다면, 아래로 한번 더 추적
	if (HitResult.bBlockingHit)
	{
		// Decal이 벽에 파고 들어가서 -direction 방향으로 위치 조절
		FVector DownStart = HitResult.ImpactPoint - (direction * 20.0f);
		FVector DownEnd = DownStart - FVector(0, 0, MaxDistance + 1000.0f);

		FHitResult DownHitResult;
		UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), DownStart, DownEnd, TraceType, false, ignores, DrawDebug_Decal, DownHitResult, true);

		if (DownHitResult.bBlockingHit)
			DecalLocation = DownHitResult.ImpactPoint;

		else
			DecalLocation = HitResult.ImpactPoint;
	}

	// Decal Spawn 사정거리 제한
	// 최대 거리를 넘어가도 Hit가 안됐을 때는 최대거리 지점에 Decal Spawn
	else
	{
		FVector DownStart = end;
		FVector DownEnd = DownStart - FVector(0, 0, MaxDistance + 1000.0f);

		FHitResult DownHitResult;
		UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), DownStart, DownEnd, TraceType, false, ignores, DrawDebug_Decal, DownHitResult, true);

		// 아래로 추적했을 때 Hit가 되면 그 지점에 Decal Spawn
		if (DownHitResult.bBlockingHit)
			DecalLocation = DownHitResult.ImpactPoint;

		// 그래도 Hit가 안되면 기존처럼 최대거리 지점에 Decal Spawn
		else
			DecalLocation = end;

	}

	Decal_Cursor->SetWorldLocation(DecalLocation);
}
