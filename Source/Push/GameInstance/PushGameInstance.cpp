#include "GameInstance/PushGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void UPushGameInstance::CreateSession()
{
	IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if(SubsystemRef)
	{
		SessionInterface = SubsystemRef->GetSessionInterface();
		if(SessionInterface)
		{
			FOnlineSessionSettings SessionCreationInfo;
			SessionCreationInfo.bIsDedicated = true;
			SessionCreationInfo.bShouldAdvertise = true;
			SessionCreationInfo.NumPublicConnections = 10;
			SessionCreationInfo.bAllowJoinInProgress = true;
			SessionCreationInfo.bUsesPresence = false;

			//SessionCreationInfo.Set()
		}
	}
}
