#include "PointDecal.h"
#include "Components/DecalComponent.h"
#include "Global.h"

APointDecal::APointDecal()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Root, "Root", RootComponent);
	Helpers::CreateComponent(this, &PointDecal, "PointDecal", Root);
	PointDecal->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	PointDecal->SetVisibility(true);

}

void APointDecal::BeginPlay()
{
	Super::BeginPlay();

	Dynamic = PointDecal->CreateDynamicMaterialInstance();
	PointDecal->SetDecalMaterial(Dynamic);

	CurrentTime = 0.0f;
	InterpSpeed = MaxRadius / DecalTime;
}

void APointDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FString message = FString::Printf(TEXT("DecalTime : %f, InterpSpeed : %f"), DecalTime, InterpSpeed);
	//CLog::Print(message);

	CurrentTime += DeltaTime;

	if (CurrentTime + Correction <= DecalTime)
	{
		Radius = FMath::Min(Radius + InterpSpeed * DeltaTime, MaxRadius);
		Dynamic->SetScalarParameterValue("Radius", Radius);
	}

	else
	{
		PointDecal->SetVisibility(false);
		Destroy();
	}

}

void APointDecal::SetDecalTime(float InDecalTime)
{
	DecalTime = InDecalTime;
}
