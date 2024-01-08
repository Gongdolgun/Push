// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Damageable.h"
#include "PushCharacter.generated.h"

UCLASS(config = Game)
class APushCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	APushCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(VisibleInstanceOnly)
		class UWDG_EffectBase* widget;

	class ASkill* SkillActor;

	//2024_01_02 서동주 Hit Interface 적용
	//다른 Actor에서 피격 시 Hit_Implementation을 Call해서 해주세요
	//virtual void Hit(const FHitData& InHitData) override {};
	virtual void Hit_Implementation(const FHitData& InHitData) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
		class UResourceComponent* ResourceComponent;

	UPROPERTY(VisibleAnywhere)
		class UMoveComponent* MoveComponent;

	UPROPERTY(EditAnywhere)
		class USkillComponent* SkillComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASkill> SkillClass;


public:
	//모든 서버와 클라이언트에게 보여주는 Montage 실행 시 Client에서 호출하는 함수
	UFUNCTION(Server, Reliable)
		void PlayAnimMontageRep(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate);

	//Client에서 호출하면 안됩니다.
	UFUNCTION(NetMulticast, Reliable)
		void PlayAnimMontageMC(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate);

	UFUNCTION(Server, Reliable)
		void SetSpawnlocationRep(FVector InVector);

	UFUNCTION(NetMulticast, Reliable)
		void SetSpawnlocationNMC(FVector InVector);

	//Testing!!
	UFUNCTION(BlueprintCallable)
		void Test();
};

