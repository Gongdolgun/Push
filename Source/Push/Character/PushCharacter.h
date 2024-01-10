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

<<<<<<< Updated upstream
	// 2024_01_02 ������ Hit Interface ����
	//�ٸ� Actor���� �ǰ� �� Hit_Implementation�� Call�ؼ� ���ּ���
	virtual void Hit(const FHitData& InHitData) override {};
	virtual void Hit_Implementation(const FHitData& InHitData) override;

	// 2024_01_05 Material Change ����
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerChangeMaterial(ACharacter* Character, FLinearColor NewColor);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
		void MulticastChangeMaterial(ACharacter* Character, FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
		void Create_DynamicMaterial(class ACharacter* InCharacter);

	UFUNCTION(BlueprintCallable)
		void Change_Color(class ACharacter* InCharacter, FLinearColor InColor);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
=======
    class ASkill* SkillActor;

    //2024_01_02 ������ Hit Interface ����
    virtual void Hit(AActor* InAttacker, const FHitData& InHitData) override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* CameraBoom;
>>>>>>> Stashed changes

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere)
        class UResourceComponent* ResourceComponent;

    UPROPERTY(VisibleAnywhere)
        class UMoveComponent* MoveComponent;

<<<<<<< Updated upstream
=======
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        class USkillComponent* SkillComponent;

    UPROPERTY(EditAnywhere)
        class UBuffComponent* BuffComponent;

    UPROPERTY(EditAnywhere)
        class UItemComponent* ItemComponent;

    UPROPERTY(EditAnywhere)
        TSubclassOf<class ASkill> SkillClass;

public:
    //��� ������ Ŭ���̾�Ʈ���� �����ִ� Montage ���� �� Client���� ȣ���ϴ� �Լ�
    UFUNCTION(Server, Reliable)
        void PlayAnimMontageRep(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate);

    //Client���� ȣ���ϸ� �ȵ˴ϴ�.
    UFUNCTION(NetMulticast, Reliable)
        void PlayAnimMontageMC(ACharacter* InCharacter, UAnimMontage* InMontage, const float PlayRate);

    UFUNCTION(Server, Reliable)
        void SetSpawnlocationRep(FVector InVector);

    UFUNCTION(NetMulticast, Reliable)
        void SetSpawnlocationNMC(FVector InVector);

    UFUNCTION(Server, Reliable)
        void LaunchServer(FVector InLaunch);

    UFUNCTION(NetMulticast, Reliable)
        void LaunchNMC(FVector InLaunch);

    // 2024_01_05 Material Change ����
    UFUNCTION()
        void Create_DynamicMaterial(class ACharacter* InCharacter);

    UFUNCTION()
        void Change_Color(FLinearColor InColor);

    //Testing!!
    UFUNCTION(BlueprintCallable)
        void Test();
>>>>>>> Stashed changes
};
