#include "Area.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AArea::AArea()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AArea::BeginPlay()
{
	Super::BeginPlay();

	
}

void AArea::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AArea::SkillPressed()
{
	Super::SkillPressed();

	FVector start = Owner->GetActorLocation();
	FVector end = start + (Owner->GetActorForwardVector() * MaxDistance);

	FHitResult HitResult;
	TArray<AActor*> ignores;
	ignores.Add(Owner);

	UKismetSystemLibrary::LineTraceSingle(
		Owner->GetWorld(), start, end, TraceType,
		false, ignores, DrawDebug, HitResult, true);
		//Owner->GetWorld(), start, end, TraceTypeQuery2,
		//false, ignores, EDrawDebugTrace::ForDuration, HitResult, true);

	FVector DecalLocation = end;

	if (!HitResult.bBlockingHit)
	{
		FVector StartSecondTrace = end;
		FVector EndSecondTrace = end + FVector(0, 0, -10000);
		FHitResult HitResultSecondTrace;
		UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), StartSecondTrace, EndSecondTrace,
			TraceType, false, ignores, DrawDebug, HitResultSecondTrace, true);

		if (HitResultSecondTrace.bBlockingHit)
		{
			DecalLocation = HitResultSecondTrace.ImpactPoint;
		}
	}

	UGameplayStatics::SpawnDecalAtLocation(Owner->GetWorld(), Decal, DecalScale, DecalLocation);
	

}

