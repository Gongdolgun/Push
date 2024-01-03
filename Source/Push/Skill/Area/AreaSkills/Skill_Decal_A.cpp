#include "Skill/Area/AreaSkills/Skill_Decal_A.h"
#include "Components/TimelineComponent.h"
#include "Components/DecalComponent.h"
#include "Global.h"

ASkill_Decal_A::ASkill_Decal_A()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Root, "Root", RootComponent);
	Helpers::CreateComponent(this, &Decal_Ground, "Decal_Ground", Root);
	Decal_Ground->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	Decal_Ground->SetVisibility(true);

	Helpers::CreateActorComponent<UTimelineComponent>(this, &DecalTimeline, "DecalTimeline");
	InterpFunction.BindUFunction(this, FName("OnTimelineUpdate"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
}

void ASkill_Decal_A::BeginPlay()
{
	Super::BeginPlay();
	
	if (Curve_DecalGround)
	{
		Dynamic = Decal_Ground->CreateDynamicMaterialInstance();
		Decal_Ground->SetDecalMaterial(Dynamic);

		DecalTimeline->AddInterpFloat(Curve_DecalGround, InterpFunction, FName("Alpha"));
		DecalTimeline->SetTimelineFinishedFunc(TimelineFinished);
		DecalTimeline->SetLooping(false);
		DecalTimeline->SetIgnoreTimeDilation(true);

		// 커브의 최소, 최댓값 구하기
		Curve_DecalGround->GetTimeRange(Curve_MinTime, Curve_MaxTime);

		// 타이머를 설정합니다.
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
			{
				// 커브의 끝 시간 - 0.3초 전에 출력
				//CLog::Print("11");
			}, Curve_MaxTime - Minus, false);


		OnTimelinePlayfromStart();
	}
	
}

void ASkill_Decal_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASkill_Decal_A::OnTimelinePlayfromStart()
{
	// Timeline PlayFromStart
	DecalTimeline->PlayFromStart();
}

void ASkill_Decal_A::OnTimelineUpdate(float Value)
{
	// Timeline Update
	Dynamic->SetScalarParameterValue(FName("Radius"), Value);
	

}

void ASkill_Decal_A::OnTimelineFinished()
{
	Decal_Ground->SetVisibility(false);
	
	Destroy();
}
