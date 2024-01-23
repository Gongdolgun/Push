#include "Components/ResourceComponent.h"
#include "PlayerController/PushPlayerController.h"
#include "Character/PushCharacter.h"
#include "HUD/MainHUD.h"
#include "Widgets/KillDeathUI.h"
#include "Net/UnrealNetwork.h"
#include "Global.h"
#include "Widgets/MainUI.h"

UResourceComponent::UResourceComponent()
{
}

void UResourceComponent::SetHP_Server_Implementation(float hp)
{
	SetMaxHP_NMC(hp);
}


void UResourceComponent::SetHP_NMC_Implementation(float hp)
{
	HP = hp;
}

void UResourceComponent::SetMaxHP_Server_Implementation(float maxHP)
{
	SetMaxHP_NMC(maxHP);
}

void UResourceComponent::SetMaxHP_NMC_Implementation(float maxHP)
{
	MaxHP = maxHP;
}

// 2024.01.02 이현중
// 현재 수치에 Value값을 현재HP에 plus 최대값은 0~MaxHP까지

void UResourceComponent::AdjustHP_Server_Implementation(int InValue)
{
	AdjustHP_NMC(InValue);
}

void UResourceComponent::AdjustHP_NMC_Implementation(int InValue)
{
	HP = FMath::Clamp(HP + InValue, 0.0f, MaxHP);
}

void UResourceComponent::AdjustHP(int InValue)
{
	HP = FMath::Clamp(HP + InValue, 0.0f, MaxHP);
}

void UResourceComponent::OnKillDeathUI()
{
	TWeakObjectPtr<APushCharacter> Owner = Cast<APushCharacter>(GetOwner());
	TWeakObjectPtr<APushPlayerController> playerController = Cast<APushPlayerController>(Owner->GetController());

	if (false == playerController.IsValid()) return;

	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(playerController->GetHUD()) : MainHUD;

	if (false == IsValid(MainHUD)) return;

	if (MainHUD->CheckWidget("LeaderBoard"))
	{
		MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->OpenLeaderBoard();
	}
}

void UResourceComponent::OffKillDeathUI()
{
	TWeakObjectPtr<APushCharacter> Owner = Cast<APushCharacter>(GetOwner());
	TWeakObjectPtr<APushPlayerController> playerController = Cast<APushPlayerController>(Owner->GetController());

	if (false == playerController.IsValid()) return;

	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(playerController->GetHUD()) : MainHUD;

	if (false == IsValid(MainHUD)) return;

	if (MainHUD->CheckWidget("LeaderBoard"))
	{
		MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->OffLeaderBoard();
	}
}

void UResourceComponent::SetGold_Server_Implementation(int InValue)
{
	SetGold_NMC(InValue);
}

void UResourceComponent::SetGold_NMC_Implementation(int InValue)
{
	Gold = InValue;
}

int UResourceComponent::GetGold()
{
	return Gold;
}

void UResourceComponent::AdjustGold_Server_Implementation(int InValue)
{
	AdjustGold_NMC(InValue);
}


void UResourceComponent::AdjustGold_NMC_Implementation(int InValue)
{
	// 골드제한 할거면 Clamp 추가
	Gold += InValue;

	CLog::Log(Gold);
}


void UResourceComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UResourceComponent, Gold);
}

void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();


}
