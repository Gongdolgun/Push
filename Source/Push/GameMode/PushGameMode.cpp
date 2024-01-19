#include "PushGameMode.h"
#include "Character/PushCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerController/PushPlayerController.h"
#include "GameInstance/PushGameInstance.h"
#include "Utilites/CLog.h"
#include "Widgets/StoreUI.h"

namespace MatchState
{
	const FName Result = FName("Result"); // �����ǥ. ������� ���� MatchState�� ���� ����ؼ� ���
}

APushGameMode::APushGameMode()
{
	bDelayedStart = true; // true�� GameMode�� start �Ǳ� ���� waiting ����. false�� MatchState::WaitingToStart�� ��Ȱ��ȭ�Ǿ� ������� �ʴ´�

}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();

	

	/*UGameInstance* gameInstance = GetGameInstance();
	UPushGameInstance* temp = gameInstance->GetSubsystem<UPushGameInstance>();

	if(false == IsValid(temp))
	{
		temp->CreateDedicatedServerSession("127.0.0.1:7777");	
	}*/
}

void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//** '���ð� > ���ð� > ����ð�'�� �ݺ�
	if (MatchState == MatchState::WaitingToStart) // ���
	{
		// ���ð� - ����ð� + ���ӷ����ʿ� �� �ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + tempTime;
		if (CountdownTime <= 0.0f) // ���ð��� ������ ������
		{
			SetMatchState(MatchState::InProgress);
		}
	}
	else if (MatchState == MatchState::InProgress) // ���
	{
		// ���ð� - ����ð� + ���ӷ����ʿ� �� �ð� + ������ ���ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + tempTime;
		if (CountdownTime <= 0.0f)
		{
			SetMatchState(MatchState::Result); // �����ǥ
		}
	}
	else if (MatchState == MatchState::Result) // �����ǥ
	{
		// ���ð� - ���� �ð� + ���ӷ����ʿ� �� �ð� + ������ ���ð� + ������ �����ǥ�ð�
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime + MatchTime + ResultTime + tempTime;
		if (CountdownTime <= 0.0f) 
		{
			tempTime = GetWorld()->GetTimeSeconds();
			SetMatchState(MatchState::WaitingToStart); 
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

	APushPlayerController* controller = Cast<APushPlayerController>(NewPlayer);

	if (controller == nullptr)
		return;

	APushCharacter* character = Cast<APushCharacter>(controller->GetPawn());

	if (character == nullptr)
	{
		CLog::Log("No Character");
		return;
	}

	if(index >= Colors.Num() - 1)
		character->BodyColor = FLinearColor::Black;
	else
		character->BodyColor = Colors[index++];
}
