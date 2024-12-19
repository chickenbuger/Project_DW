// Fill out your copyright notice in the Description page of Project Settings.

/** Manager */
#include "DreamWorld/FrameWork/ActorComponent/AC_AttackManager.h"

/** Instance */
#include "DreamWorld/FrameWork/Main/GI_Main.h"

/** Enemy */
#include "DreamWorld/Enemy/NC_EnemyBase.h"

/** Struct */
#include "DreamWorld/Struct/SkillStruct.h"

/** Draw */
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UAC_AttackManager::UAC_AttackManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAC_AttackManager::CallAttemptAttack(const int In_SkillID)
{
	// CSV 파일을 기반으로 Data Table을 제작하여 Skill에 대한 데이터 추가 필요
	// Data Table 에는 Type별 함수 따로 제작
	// 스킬에 대한 정보는 TARRAY를 통해 실행 (공격 판정이 원형과 호가 같이 있을 수 있음)
	// TSet을 통해 중복되는 데이터 제거 후 데미지 처리
	TObjectPtr<UWorld> world = GetWorld();
	if (nullptr == world) return;

	TObjectPtr<UGI_Main> gameInstance = Cast<UGI_Main>(world->GetGameInstance());
	if (nullptr == gameInstance) return;

	FSkillData* DT_skill = gameInstance->LoadSkillDataTable(In_SkillID);
	if (nullptr == DT_skill) return;

	TSet<TObjectPtr<ANC_EnemyBase>> TotalEnemys;

	for (int index = 0; index < DT_skill->m_Attack_Type.Num(); index++)
	{
		//index번 째 공격 타입
		const EAttackCheckType& attacktype = DT_skill->m_Attack_Type[index]; 
		FVector range = DT_skill->m_Attack_Range[index];
		TArray<FHitResult>	OutHits;

		//HitActor가 존재하는지 체크
		bool isSucc = false;
		if (attacktype == EAttackCheckType::Box)
		{
			//range : x,y,z
			if (CheckBoxTypeAttack(range, OutHits)) isSucc = true;
		}
		else if (attacktype == EAttackCheckType::Circle)
		{
			//range : r
			if (CheckCircleTypeAttack(range.X, OutHits)) isSucc = true;
		}
		else if (attacktype == EAttackCheckType::Arc)
		{
			//range : r, start angle, end angle
			//if (CheckBoxTypeAttack(range, OutHits)) isSucc = true;
		}

		if (isSucc)
		{
			for (const FHitResult& OutHit : OutHits)
			{
				TObjectPtr<ANC_EnemyBase> enemy = Cast<ANC_EnemyBase>(OutHit.GetActor());
				if (nullptr == enemy)
				{
					continue;
				}
				
				if (!TotalEnemys.Contains(enemy))
				{
					TotalEnemys.Add(enemy);
				}
			}
		}
	}

	for (const TObjectPtr<ANC_EnemyBase>& enemy : TotalEnemys)
	{
		enemy->RecieveDamage(DT_skill->m_Attack_Damage);
	}
}

// Called when the game starts
void UAC_AttackManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UAC_AttackManager::CheckBoxTypeAttack(const FVector In_BoxHalfSize, TArray<FHitResult>& OutHits)
{
	const FVector Location			= m_OwnerCharacter->GetActorLocation();
	const FVector Forward			= m_OwnerCharacter->GetActorForwardVector();
	
	const FVector ModifyLoc			= Forward * 5.f;

	const FVector Start				= Location + ModifyLoc;
	const FVector End				= Location + Forward * In_BoxHalfSize.X * 2 + ModifyLoc;

	const FVector BoxHalfSize		= FVector(0.f,In_BoxHalfSize.Y, In_BoxHalfSize.Z);//In_BoxHalfSize;
	const FRotator Orientation		= m_OwnerCharacter->GetActorRotation();

	ECollisionChannel TraceChannel	= ECC_GameTraceChannel4;

	FCollisionShape CollisionShape	= FCollisionShape::MakeBox(BoxHalfSize);

	FCollisionQueryParams Params;

	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		Start, 
		End,
		Orientation.Quaternion(),
		TraceChannel,
		CollisionShape,
		Params
	);

#if DEBUGMODE 
	//Box Size
	const FVector DrawPos(Start.X + (End.X - Start.X) / 2.0f, Start.Y + (End.Y - Start.Y) / 2.0f, Start.Z);
	DrawDebugBox(GetWorld(), DrawPos, In_BoxHalfSize, Orientation.Quaternion(), FColor::Green, false, 2.0f);

	//Line Check
	DrawDebugLine(GetWorld(), Start		, FVector(Start.X, Start.Y, Start.Z + 100)			, FColor::Red, false, 2.0f);
	DrawDebugLine(GetWorld(), DrawPos	, FVector(DrawPos.X, DrawPos.Y, DrawPos.Z + 100)	, FColor::Red, false, 2.0f);
	DrawDebugLine(GetWorld(), End		, FVector(End.X, End.Y, End.Z + 100)				, FColor::Red, false, 2.0f);
#endif

#if LOGMODE
	UE_LOG(LogTemp,Warning,TEXT("Start : %s  End : %s"),*Start.ToString(),*End.ToString())
#endif

	if (bHit)
	{
#if DEBUGMODE 
		for (const FHitResult& OutHit : OutHits)
		{
			DrawDebugBox(GetWorld(), OutHit.ImpactPoint, BoxHalfSize, Orientation.Quaternion(), FColor::Red, false, 2.0f);
		}
#endif
		return true;
	}

	return false;
}

bool UAC_AttackManager::CheckCircleTypeAttack(const float In_Radius, TArray<FHitResult>& OutHits)
{
	const FVector AttackPoint = m_OwnerCharacter->GetActorLocation();

	ECollisionChannel TraceChannel	= ECC_GameTraceChannel4;
	FCollisionShape CollisionShape	= FCollisionShape::MakeSphere(In_Radius);

	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		AttackPoint,
		AttackPoint,
		FQuat::Identity,
		TraceChannel,
		CollisionShape
	);

#if DEBUGMODE 
	FRotator DesiredAngleZ = m_OwnerCharacter->GetActorRotation();
	DrawCircle(GetWorld(), AttackPoint,
		DesiredAngleZ.RotateVector(FVector(1, 0, 0)), DesiredAngleZ.RotateVector(FVector(0, 1, 0)), 
		FColor::Green, In_Radius, 50, false, 2.0f);
#endif

	if (bHit)
	{
		for (const FHitResult& OutHit : OutHits)
		{
#if DEBUGMODE 
			DesiredAngleZ = OutHit.GetActor()->GetActorRotation();
			DrawCircle(GetWorld(), AttackPoint,
				DesiredAngleZ.RotateVector(FVector(1, 0, 0)), DesiredAngleZ.RotateVector(FVector(0, 1, 0)),
				FColor::Red, In_Radius, 50, false, 2.0f);
#endif
		}
		return true;
	}

	return false;
}

bool UAC_AttackManager::CheckArcTypeAttack(const FVector In_BoxHalfSize, const uint32 In_Range, TArray<FHitResult>& OutHits)
{
	return false;
}

// Called every frame
void UAC_AttackManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

