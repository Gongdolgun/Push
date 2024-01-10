#include "GameInstance/PushGameInstance.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void UPushGameInstance::CreateDedicatedServerSession(FString PassedMapPath)
{
	IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if(SubsystemRef)
	{
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();

		if(SessionPtrRef)
		{
			MapPath = PassedMapPath;

			FOnlineSessionSettings SessionCreationInfo;
			SessionCreationInfo.bIsDedicated = true;
			SessionCreationInfo.bShouldAdvertise = true;
			SessionCreationInfo.NumPublicConnections = 10;
			SessionCreationInfo.bAllowJoinInProgress = true;
			SessionCreationInfo.bAllowInvites = false;
			SessionCreationInfo.bUsesPresence = false;
			SessionCreationInfo.bAllowJoinViaPresence = false;
			SessionCreationInfo.bAllowJoinViaPresenceFriendsOnly = false;
			SessionCreationInfo.bIsLANMatch = true;

			SessionCreationInfo.Set(SEARCH_KEYWORDS, FString("PushGameInstanceSubsystem"), EOnlineDataAdvertisementType::ViaOnlineService);
			SessionPtrRef->OnCreateSessionCompleteDelegates.AddUObject(this, &UPushGameInstance::OnSessionCreationReply);
			SessionPtrRef->CreateSession(0, FName("PushGameInstanceSubsystem"), SessionCreationInfo);
		}
	}
}

void UPushGameInstance::OnSessionCreationReply(FName SessionName, bool bWasSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Session reply "));
	if(bWasSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session Creation Success "));
		GetWorld()->ServerTravel(MapPath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session Creation failed "));
	}
}

//void UPushGameInstance::CreateSession()
//{
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
