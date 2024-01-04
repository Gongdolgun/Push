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

	UFUNCTION(Server, Reliable)
		void SpawnCallOnServer(TSubclassOf<class ASkill> SpawnSkill, FVector SpawnLocation, FRotator SpawnRotation);

	UFUNCTION(NetMulticast, Reliable)
		void SpawnCallMulticast(TSubclassOf<class ASkill> SpawnSkill, FVector SpawnLocation, FRotator SpawnRotation);

};
