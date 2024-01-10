#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PushGameState.generated.h"


UCLASS()
class PUSH_API APushGameState : public AGameState
{
	GENERATED_BODY()

public:
	APushGameState();

public:
	virtual void BeginPlay() override;

//public:
//	UFUNCTION(Server, Reliable)
//		void ChangeBodyColor_Server(class APushCharacter* InCharacter, FLinearColor InColor);
//
//	UFUNCTION(NetMulticast, Reliable)
//		void ChangeBodyColor_NMC(class APushCharacter* InCharacter, FLinearColor InColor);

//public:
//	TArray<FLinearColor> BodyColors;
//	uint8 index = 0;
};

