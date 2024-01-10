#include "Objects/Ring.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "Character/PushCharacter.h"
#include "Widgets/WDG_EffectBase.h"

ARing::ARing()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent<UCapsuleComponent>(this, &RingCapsule, "RingCapsule");
	Helpers::CreateComponent<UStaticMeshComponent>(this, &RingMesh, "RingMesh", RingCapsule);

	FString path = "StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'";
	RingMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*path).Object);

	RingMesh->SetCollisionProfileName("OverlapAllDynamic");

	SetActorTickInterval(1.0f);
}

void ARing::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TargetRadius = RingCapsule->GetUnscaledCapsuleRadius();
	Refresh();
}

void ARing::BeginPlay()
{
	Super::BeginPlay();

	RingCapsule->OnComponentBeginOverlap.AddDynamic(this, &ARing::OnBeginOverlap);
	RingCapsule->OnComponentEndOverlap.AddDynamic(this, &ARing::OnEndOverlap);

	for(AActor* actor : GetWorld()->GetCurrentLevel()->Actors)
	{
		APushCharacter* character = Cast<APushCharacter>(actor);

		if (character == nullptr)
			continue;

		APlayerController* controller = Cast<APlayerController>(character->GetController());

		if (controller == nullptr)
			continue;

		UWDG_EffectBase* widget = CreateWidget<UWDG_EffectBase>(controller, DamageEffectWidget);
		widget->AddToViewport();
		widget->SetVisibility(ESlateVisibility::Visible);

		character->widget = widget;
	}
}

void ARing::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ARing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitData hitData;
	hitData.Damage = RingDamage;

	for(APushCharacter* character : OverlappedCharacters)
	{
<<<<<<< Updated upstream
		character->Hit_Implementation(hitData);
		character->widget->PlayEffect();
=======
		character->Hit(this, hitData);

		APlayerController* controller = Cast<APlayerController>(character->GetController());

		if (controller == nullptr)
			return;

		AMainHUD* hud = Cast<AMainHUD>(controller->GetHUD());

		if (hud == nullptr)
			return;

>>>>>>> Stashed changes
	}
}

void ARing::Shrink(float InRadius, float InTime)
{
	DeltaRadius = (RingCapsule->GetUnscaledCapsuleRadius() - InRadius) / (InTime * 100);
	TargetRadius = InRadius;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARing::ChangeRadius, 0.01f, true, 0.0f);
}

void ARing::ChangeRadius()
{
	float radius = RingCapsule->GetUnscaledCapsuleRadius() - DeltaRadius;
	RingCapsule->SetCapsuleRadius(radius);
	CLog::Print(radius);
	if (FMath::IsNearlyEqual(radius, TargetRadius))
		GetWorldTimerManager().ClearTimer(TimerHandle);

	float scale = radius / Base;
	RingMesh->SetWorldScale3D(FVector(scale, scale, scale * 100));
}

void ARing::Refresh()
{
	float radius = RingCapsule->GetUnscaledCapsuleRadius();
	RingCapsule->SetCapsuleRadius(radius);

	float scale = radius / Base;
	RingMesh->SetWorldScale3D(FVector(scale, scale, scale * 100));
}

void ARing::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APushCharacter* character = Cast<APushCharacter>(OtherActor);

	if (!ensure(character != nullptr))
		return;

	if(OverlappedCharacters.Contains(character))
		OverlappedCharacters.Remove(character);

}

void ARing::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APushCharacter* character = Cast<APushCharacter>(OtherActor);

	if (!ensure(character != nullptr))
		return;

	OverlappedCharacters.AddUnique(character);
}

