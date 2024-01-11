#include "Items/Item_DotItem.h"
#include "Components/BuffComponent.h"
#include "Global.h"

void AItem_DotItem::UseItem()
{
	if (Owner == nullptr)
		return;

	FVector start = Owner->GetActorLocation();
	FVector end = start + Owner->GetActorForwardVector() * 400.0f;
	TArray<AActor*> ignore;
	ignore.Add(Owner.Get());
	FHitResult result;
	UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), start, end, TraceType, false, ignore, DrawType, result, true);

	if (!result.bBlockingHit)
		return;

	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(result.Actor.Get());

	if (!buffComponent)
		return;

	CLog::Log("DebugTest");
	buffComponent->AddBuff_Server(BuffClass);
}
