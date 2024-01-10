#pragma once
#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PushGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API UPushGameInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()
		
	
public:
	UFUNCTION(BlueprintCallable)
	void CreateDedicatedServerSession(FString PassedMapPath);

	UFUNCTION()
	void OnSessionCreationReply(FName SessionName, bool bWasSuccess);

	UPROPERTY()
	FString MapPath;
};
