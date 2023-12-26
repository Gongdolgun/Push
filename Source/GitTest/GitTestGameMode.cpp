// Copyright Epic Games, Inc. All Rights Reserved.

#include "GitTestGameMode.h"
#include "GitTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGitTestGameMode::AGitTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
