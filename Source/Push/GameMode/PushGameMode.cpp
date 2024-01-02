#include "PushGameMode.h"
#include "Push/PushCharacter.h"
#include "UObject/ConstructorHelpers.h"

APushGameMode::APushGameMode()
{
<<<<<<< HEAD
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP/Character/BP_PushCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
=======

}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();
}

>>>>>>> parent of 34cbec8 (Merge branch 'Test' into HJ)
