#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EDebuff : uint8
{
	ED_None, ED_Root, ED_Freeze, ED_Bleed
};

UCLASS()
class PUSH_API UEnums : public UObject
{
	GENERATED_BODY()

};
