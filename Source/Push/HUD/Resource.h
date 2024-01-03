#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Resource.generated.h"

/** ĳ������ ����(ü��, ���� ��)�� �����ִ� UserWidget Ŭ����
 * 
 */

UCLASS(Blueprintable)
class PUSH_API UResource : public UUserWidget
{
	GENERATED_BODY()

public:
	UResource(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar; // ü�� ��

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MatchCountdownText; // �ð�
};
