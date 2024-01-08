#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSH_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void UseSkill(char InChar);

	UFUNCTION(BlueprintCallable)
		void Execute();

public:
	TMap<char, class USkillData*> SkillMap;
	ACharacter* Owner;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<USkillData> ss;

public:
	UPROPERTY(EditAnywhere)
		class USkillData* curSkillData;

	UPROPERTY(EditAnywhere, Replicated)
		FVector SpawnLocation;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};