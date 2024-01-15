#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/Structures.h"
#include "SkillData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PUSH_API USkillData : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FProduct Product;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UTexture2D* SkillTexture;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* ActionMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;*/

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASkill> Skill;

	UPROPERTY(EditAnywhere)
		float RelativeDistance = 0;

	UPROPERTY(EditAnywhere)
		FVector RelativeLocation = FVector::ZeroVector;

public:
	UFUNCTION()
	virtual void Play(ACharacter* InOwner);
	
};