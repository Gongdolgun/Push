#include "Push/GameState/PushGameState.h"
#include "Character/PushCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Global.h"

APushGameState::APushGameState()
{
	//BodyColors.Add(FLinearColor::Black);
	//BodyColors.Add(FLinearColor::Blue);
	//BodyColors.Add(FLinearColor::Green);
	//BodyColors.Add(FLinearColor::Red);
}

void APushGameState::BeginPlay()
{
	Super::BeginPlay();

	//if (HasAuthority() == false)
	//	return;

	//for(APlayerState* player : PlayerArray)
	//{
	//	CLog::Log("Get APlayerState");
	//	APushCharacter* character = Cast<APushCharacter>(player->GetPawn());

	//	if (character == nullptr)
	//		continue;

	//	CLog::Log("change body color");

	//	ChangeBodyColor_NMC_Implementation(character, BodyColors[index++]);
	//}
}

//void APushGameState::ChangeBodyColor_NMC_Implementation(APushCharacter* InCharacter, FLinearColor InColor)
//{
//	InCharacter->BodyColor = InColor;
//	InCharacter->Create_DynamicMaterial();
//	InCharacter->Change_Color();
//}
//
//void APushGameState::ChangeBodyColor_Server_Implementation(APushCharacter* InCharacter, FLinearColor InColor)
//{
//	ChangeBodyColor_NMC_Implementation(InCharacter, InColor);
//}
