#include "Area.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

AArea::AArea()
{

}

void AArea::BeginPlay()
{
	Super::BeginPlay();

	if (Owner)
	{
		FVector start = Owner->GetActorLocation();
		FVector end = start + (Owner->GetActorForwardVector() * MaxDistance);

		FHitResult HitResult;
		TArray<AActor*> ignores;
		ignores.Add(Owner);

		UKismetSystemLibrary::LineTraceSingle(
			Owner->GetWorld(), start, end, TraceTypeQuery1,
			false, ignores, DrawDebug, HitResult, true);

		if (HitResult.bBlockingHit)
		{
			// TODO :: CLOG::Print("?");
		}
	}


}

void AArea::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
