#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */

UCLASS()
class PUSH_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
