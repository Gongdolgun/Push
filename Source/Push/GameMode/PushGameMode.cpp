// Copyright Epic Games, Inc. All Rights Reserved.

#include "PushGameMode.h"
#include "Push/Character/PushCharacter.h"
#include "UObject/ConstructorHelpers.h"

APushGameMode::APushGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP/Character/BP_PushCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}