#include "PushGameMode.h"
#include "Character/PushCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerController/PushPlayerController.h"
#include "GameInstance/PushGameInstance.h"
#include "GameState/PushGameState.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Utilites/CLog.h"
#include "Global.h"
#include "Components/ResourceComponent.h"
#include "Widgets/StoreUI.h"
#include "Objects/Ring.h"
#include "Components/MoveComponent.h"

namespace MatchState
{
	const FName Round = FName("Round"); 
}

namespace MatchState
{
	const FName Result = FName("Result"); // 결과발표. 내장되지 않은 MatchState을 사용시 명시해서 사용
}

APushGameMode::APushGameMode()
{
	bDelayedStart = true; // 캐릭터가 시작부터 끝까지 계속 스폰되어 있어야하므로 MatchState::WaitingToStart를 없애고 bDelayedStart = true로 변경하였다.
	
}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	tempTime = GetWorld()->GetTimeSeconds();
	CountdownTime = WarmupTime;
	CurrentTime = 0.0f;

	PushGameState = Cast<APushGameState>(GameState);

	if(PushGameState == nullptr){ // 예외처리
		CLog::Log("pushGameState == nullptr !!");
		return;
	}

	TWeakObjectPtr<UWorld> world = GetWorld();

	if (world.IsValid())
	{
		if (IsValid(RingClass))
		{
			Ring = world->SpawnActor<ARing>(RingClass);
			Ring->SetActorLocation(FVector(-45800.f, 15700.f, -24000.f));
		}
	}
}

void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PushGameState->SetTime(CurrentTime);
	if (MatchState == MatchState::InProgress) // 상점
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f)
		{
			CountdownTime = RoundTime[Round];
			tempTime = GetWorld()->GetTimeSeconds();
			SetMatchState(MatchState::Round);
		}
	}
	else if (MatchState == MatchState::Round) // 라운드s
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f)
		{
			if (RoundTime.Num() - 1 <= Round)
			{
				tempTime = GetWorld()->GetTimeSeconds();
				CountdownTime = ResultTime;
				Round = 0;
				SetMatchState(MatchState::Result); // 결과발표
			}
			else
			{
				if (Ring.Get() != nullptr)
					Ring.Get()->Shrink(RingRadius[Round], 10);

				CountdownTime = RoundTime[++Round];
				tempTime = GetWorld()->GetTimeSeconds();
			}
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f) 
		{
			tempTime = GetWorld()->GetTimeSeconds();
			CountdownTime = WarmupTime;
			SetMatchState(MatchState::InProgress);
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

	CLog::Log("Post Login In the Game");
	

	character->BodyColor = Colors[index++];

	AllPC.Add(NewPlayer);
	UpdatePlayerList();
}

void APushGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerController* playercontroller = Cast<APlayerController>(Exiting);
	AllPC.Empty();

	UpdatePlayerList();
}

void APushGameMode::UpdatePlayerList()
{
	// 플레이어 리스트를 비워주고, GameState에서 Player의 이름을 가져와서 세팅
	PlayerListData.Empty();

	for (APlayerController* playerContrller : AllPC)
	{
		if (playerContrller)
		{
			APushPlayerController* pushController = Cast<APushPlayerController>(playerContrller);
			APawn* pawn = playerContrller->GetPawn();
			// 업데이트가 제대로 안되고 게임이 시작할 경우가 생겨서 0.2초뒤에 다시 함수 실행
			if (!pawn)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(
					TimerHandle, this, &APushGameMode::UpdatePlayerList, 0.2f, false);
			}

			else
			{
				// Lobby에서 입력된 이름인 CustomPlayerName이 출력되도록 변경
				APushCharacter* pushCharacter = Cast<APushCharacter>(pawn);
				if (pushCharacter)
				{
					UResourceComponent* resource = Helpers::GetComponent<UResourceComponent>(pushCharacter);

					PlayerData.PlayerName = pushCharacter->CustomPlayerName;
					PlayerData.Gold = resource->GetGold();
					PlayerData.Kill = resource->GetKill();
					PlayerData.Death = resource->GetDeath();

					PlayerListData.Add(PlayerData);
				}
			}
		}
	}

	// 플레이어 리스트 업데이트
	for (APlayerController* playerController : AllPC)
	{
		APushPlayerController* pushPlayerController = Cast<APushPlayerController>(playerController);

		if (pushPlayerController)
			pushPlayerController->UpdatePlayerList_Server(PlayerListData);
	}
}

void APushGameMode::SetMatchState(FName NewState)
{
	Super::SetMatchState(NewState);

	if(NewState == MatchState::Result)
	{
		PushGameState->GiveGold(MoneyPerRank);
	}
}
