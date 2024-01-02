#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PushCharacter.generated.h"

UCLASS(config=Game)
class APushCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	APushCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:

	void OnResetVR();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UFUNCTION(BlueprintCallable)
		void NumberPressed();

<<<<<<< HEAD
	UFUNCTION(BlueprintCallable)
		void OnSkillClicked();
=======
	class ASkill* SkillActor;
>>>>>>> parent of 16cf9d5 (2023.12.29 이현중)

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASkill> SubclassSkill;

private:
	TWeakObjectPtr<class ASkill_Meteor_A> SkillActor;

	UPROPERTY(VisibleAnywhere)
		class UResourceComponent* ResorceComponent;
	UPROPERTY(VisibleAnywhere)
		class UMoveComponent* MoveComponent;
};

