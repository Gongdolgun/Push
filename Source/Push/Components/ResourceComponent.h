#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUSH_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UResourceComponent();

	FORCEINLINE float GetHP() { return HP; }
	FORCEINLINE float GetMaxHP() { return MaxHP; }

	//2024.01.09 이현중
	//기존 INLINE함수 RPC를 이용한 함수로 변경
	UFUNCTION(Server, Reliable)
		void SetHP_Server(float hp);

	UFUNCTION(Server, Reliable)
		void SetMaxHP_Server(float maxHP);

	UFUNCTION(Server, Reliable)
		void AdjustHP_Server(int InValue);

	UFUNCTION(NetMulticast, Reliable)
		void SetHP_NMC(float hp);

	UFUNCTION(NetMulticast, Reliable)
		void SetMaxHP_NMC(float maxHP);

	UFUNCTION(NetMulticast, Reliable)
		void AdjustHP_NMC(int InValue);

	void AdjustHP(int InValue);

	// 2024_01_04 박성우 - Tab키 입력 시 KillDeath 위젯 띄우기
	void OnKillDeathUI();
	void OffKillDeathUI();

	// 2024_01_15 문인수 - Gold
	UFUNCTION(Server, Reliable)
		void SetGold_Server(int InValue);

	UFUNCTION(NetMulticast, Reliable)
		void SetGold_NMC(int InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetGold();

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void AdjustGold_Server(int InValue);

	UFUNCTION(NetMulticast, Reliable)
		void AdjustGold_NMC(int InValue);

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
		meta = (AllowPrivateAccess))
		float HP = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
	meta = (AllowPrivateAccess))
		float MaxHP = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
		meta = (AllowPrivateAccess))
		int32 Gold = 0;

	UPROPERTY()
	class AMainHUD* MainHUD;

};
