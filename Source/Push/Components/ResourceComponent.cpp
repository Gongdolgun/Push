#include "Components/ResourceComponent.h"

#include "GameFramework/Character.h"

UResourceComponent::UResourceComponent()
{
	//SetIsReplicated(true);
	Owner = Cast<ACharacter>(GetOwner());
	int a = 0;
}

//void UResourceComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(UResourceComponent, HP);
//}

void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

}

