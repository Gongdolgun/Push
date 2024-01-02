#include "Items/Item_FastMove.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MoveComponent.h"

void AItem_FastMove::BeginPlay()
{
	Super::BeginPlay();
}

void AItem_FastMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem_FastMove::Use()
{
	UCharacterMovementComponent* movementComponent = Helpers::GetComponent<UCharacterMovementComponent>(Owner.Get());
	UMoveComponent* moveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());

	float speedPercent = moveComponent->GetSpeedPercent() * ((PlusSpeedPercent + 100) / 100);
	
	//TODO : 플레이어 이동속도는 무브컴포넌트x 캐릭터 무브먼트가 해야할 일 movement도 변경해주자
	// 2024.01.02  이현중
	//플레이어 이동속도 증가
	movementComponent->MaxWalkSpeed = 2000;
}
