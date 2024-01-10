#include "PushGameMode.h"
#include "Push/Character/PushCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Global.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameState/PushGameState.h"
#include "PlayerController/PushPlayerController.h"
<<<<<<< Updated upstream
=======
#include "Widgets/StoreUI.h"
#include "Global.h"
#include "GameFramework/GameStateBase.h"
>>>>>>> Stashed changes

namespace MatchState
{
	const FName Result = FName("Result");
}

APushGameMode::APushGameMode()
{
	bDelayedStart = true; // true�� GameMode�� start �Ǳ� ���� waiting ����

}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();

}

void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MatchState == MatchState::WaitingToStart) // ���
	{
		// ���ð� - ����ð� + ���ӷ����ʿ� �� �ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.0f) // ���ð��� ������ ������
		{
			StartMatch(); // ���
		}
	}
	else if (MatchState == MatchState::InProgress) // ���
	{
		// ���ð� - ����ð� + ���ӷ����ʿ� �� �ð� + ������ ���ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime;
		if (CountdownTime <= 0.0f)
		{
			SetMatchState(MatchState::Result); // �����ǥ
		}
	}
	else if (MatchState == MatchState::Result) // �����ǥ
	{
		// ���ð� - ���� �ð� + ���ӷ����ʿ� �� �ð� + ������ ���ð� + ������ �����ǥ�ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + ResultTime;
		if (CountdownTime <= 0.0f)
		{
			RestartGame(); // ��� �����. GameMode ���� Ŭ������ ���ǵ� �Լ� ��
		}
	}

}

void APushGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	// GameMode�� MatchState�� ����Ǹ� �������� �ش�Ǵ� PlayerController�� ã�� MatchState�� �����Ѵ�.
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		TWeakObjectPtr<APushPlayerController> SelectedPlayer = Cast<APushPlayerController>(*It);
		if (SelectedPlayer.IsValid())
		{
			SelectedPlayer->OnMatchStateSet(MatchState);
		}
	}
}

void APushGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

<<<<<<< Updated upstream
	APushPlayerController* Controller = Cast<APushPlayerController>(NewPlayer);

	if (Controller)
	{
		//if (HasAuthority())
		//{
		//	CLog::Print("Server");
		//}
		//
		//else
		//{
		//	CLog::Print("Client");
		//}
	}
	
	ULocalPlayer* LocalPlayer = Controller->GetLocalPlayer();

	//CLog::Print(LocalPlayer);

	APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		//CLog::Print(PlayerState->GetPlayerId());
	}
}

=======
	

}


>>>>>>> Stashed changes
