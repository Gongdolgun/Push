#include "GameState/LobbyGameState.h"
#include "Global.h"

void ALobbyGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//CurrentServerTime = GetDefaultGameMode()->GetWorld()->GetTimeSeconds();///GetServerWorldTimeSeconds/();
	//
	//CLog::Log(CurrentServerTime);
	
}

//void ALobbyGameState::UpdateMatchStartCountdownWidget()
//{
//	
//}
//
//void ALobbyGameState::OnRep_MatchStartCountdown()
//{
//	
//	MatchCountDown();
//}
//
//void ALobbyGameState::MatchCountDown()
//{
//	MatchStartCountdown -= 1.f;
//}

//void ALobbyGameState::Server_SendCurrentTimeToClient_Implementation(float CurrentTime)
//{
//	if (HasAuthority())
//	{
//		CurrentServerTime = FPlatformTime::Seconds();
//		//float CurrentTime = FPlatformTime::Seconds();
//		//Server_SendCurrentTimeToClient(CurrentTime);
//	}
//	else
//	{
//		Client_ReceiveCurrentTimeFromServer();
//	}
//}
//
//void ALobbyGameState::Client_ReceiveCurrentTimeFromServer_Implementation(float CurrentTime)
//{
//	float LocalTime = FPlatformTime::Seconds();
//    float TimeDifference = CurrentTime - LocalTime;
//}
