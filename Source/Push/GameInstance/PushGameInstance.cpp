//#include "GameInstance/PushGameInstance.h"
//#include "OnlineSubsystem.h"
//#include "OnlineSubsystemUtils.h"
//#include "GameMode/PushGameMode.h"
//
//void UPushGameInstance::CreateSession()
//{
//	//IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(this->GetWorld());
//	//if(SubsystemRef)
//	//{
//	//	SessionInterface = SubsystemRef->GetSessionInterface();
//	//	if(SessionInterface)
//	//	{
//	//		FOnlineSessionSettings SessionCreationInfo;
//	//		SessionCreationInfo.bIsDedicated = true;
//	//		SessionCreationInfo.bShouldAdvertise = true;
//	//		SessionCreationInfo.NumPublicConnections = 10;
//	//		SessionCreationInfo.bAllowJoinInProgress = true;
//	//		SessionCreationInfo.bUsesPresence = false;
//
//	//		//SessionCreationInfo.Set()
//	//	}
//	//}
//
//
//	IOnlineSubsystem* onlineSub = IOnlineSubsystem::Get();
//	if (onlineSub != nullptr)
//	{
//		IOnlineSessionPtr sessionInt = Online::GetSessionInterface();
//		AGameModeBase* gameMode = Cast<AGameModeBase>(this->GetWorld()->GetAuthGameMode());
//
//		if (sessionInt.IsValid())
//		{
//			TSharedPtr<class FMyOnlineSessionSettings> gameHostSettings = MakeShareable(new FMyOnlineSessionSettings(true, false, 4));
//
//			gameHostSettings->Set(SETTING_GAMEMODE, FString(*gameMode->GetName()), EOnlineDataAdvertisementType::ViaOnlineService);
//			gameHostSettings->Set(SETTING_MAPNAME, GetWorld()->GetMapName(), EOnlineDataAdvertisementType::ViaOnlineService);
//			gameHostSettings->bUsesPresence = false;
//			gameHostSettings->bIsLANMatch = true;
//			gameHostSettings->bAllowInvites = true;
//			gameHostSettings->bIsDedicated = true;
//			gameHostSettings->bShouldAdvertise = true;
//			gameHostSettings->bAllowJoinInProgress = true;
//			gameHostSettings->bAllowJoinViaPresence = false;
//			gameHostSettings->bAllowJoinViaPresenceFriendsOnly = false;
//
//			this->hostSettings = gameHostSettings;
//
//			this->OnCreateSessionCompleteDelegateHandle = sessionInt->AddOnCreateSessionCompleteDelegate_Handle(this->OnCreateSessionCompleteDelegate);
//
//			sessionInt->CreateSession(0, NAME_GameSession, *this->hostSettings);
//		}
//	}
//}
