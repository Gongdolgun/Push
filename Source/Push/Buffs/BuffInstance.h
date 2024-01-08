#pragma once

#include "CoreMinimal.h"
#include "BuffInstance.generated.h"

UCLASS()
class PUSH_API UBuffInstance : public UObject
{
	GENERATED_BODY()

	friend class UBuffComponent;
public:
	UBuffInstance();
	 ~UBuffInstance();

public:
	FORCEINLINE void SetOwner(TWeakObjectPtr<ACharacter> owner) { Owner = owner; }

public:
	UFUNCTION()
		virtual void OnEffect(){}
	UFUNCTION()
		virtual void OffEffect(){}

protected:
	TWeakObjectPtr<ACharacter> Owner;

	UPROPERTY(EditAnywhere)
		UTexture2D* UIImage;

	UPROPERTY(EditAnywhere)
		float LifeTime;

	float curTime = 0;
};
