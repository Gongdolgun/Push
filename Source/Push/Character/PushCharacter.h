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

	//2024_01_02 ������ Hit Interface ����
	virtual void Hit(AActor* InAttacker, const FHitData& InHitData) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UResourceComponent* ResourceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMoveComponent* MoveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkillComponent* SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UBuffComponent* BuffComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UItemComponent* ItemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UShopComponent* ShopComponent;

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
	void Create_DynamicMaterial();
	void Change_Color(FLinearColor InColor);

	//Testing!!
	UFUNCTION(BlueprintCallable)
		void Test();

public:
	UPROPERTY(Replicated)
		FLinearColor BodyColor;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};

