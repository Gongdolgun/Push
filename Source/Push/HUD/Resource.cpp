#include "HUD/Resource.h"
#include "Global.h"

UResource::UResource(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (HealthBar == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("binding HealthBar is failed. Check WDG name to match HealthBar variable")));
		//CLog::Print("binding HealthBar is failed. Check WDG name to match HealthBar variable");
	}
}
