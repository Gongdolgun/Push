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
	UFUNCTION(BlueprintCallable)
		void UseSkill(TSubclassOf<class USkillData> SkillData);

	UFUNCTION(BlueprintCallable)
		void Execute();

public:
	ACharacter* Owner;

public:
	UPROPERTY(EditAnywhere)
		class USkillData* curSkillData;

	UPROPERTY(EditAnywhere, Replicated)
		FVector SpawnLocation;


	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable)
		void SetCurSkillData_Server(TSubclassOf<class USkillData> SkillData);

	UFUNCTION(NetMulticast, Reliable)
		void SetCurSkillData_NMC(TSubclassOf<class USkillData> SkillData);
};
