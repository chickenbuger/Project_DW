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

void UAC_AttackManager::CallAttemptBoxAttack(TObjectPtr<AActor> in_Player,const FVector in_AttackArea, float in_Damage)
{
	TArray<FHitResult> OutHits;

	if (!CheckTheScopeOfTheBoxAttack(in_AttackArea, 100.f, OutHits))
	{
		return;
	}

	for (const FHitResult& OutHit : OutHits)
	{
		TObjectPtr<ANC_EnemyBase> enemy = Cast<ANC_EnemyBase>(OutHit.GetActor());
		if (nullptr == enemy)
		{
			continue;
		}

		enemy->RecieveDamage(in_Damage);
	}
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
			//if (CheckBoxTypeAttack(range, OutHits)) isSucc = true;
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
	const FVector Location = m_OwnerCharacter->GetActorLocation();
	const FVector Forward = m_OwnerCharacter->GetActorForwardVector();
	const FVector Start = Location;
	const FVector End = Location + Forward * In_BoxHalfSize.X;

	const FVector BoxHalfSize = In_BoxHalfSize;
	const FRotator Orientation = m_OwnerCharacter->GetActorRotation();

	ECollisionChannel TraceChannel = ECC_GameTraceChannel4;

	FCollisionShape CollisionShape = FCollisionShape::MakeBox(BoxHalfSize);

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
	DrawDebugBox(GetWorld(), Start, BoxHalfSize, Orientation.Quaternion(), FColor::Green, false, 2.0f);
#endif

	if (bHit)
	{
		for (const FHitResult& OutHit : OutHits)
		{
#if DEBUGMODE 
			DrawDebugBox(GetWorld(), OutHit.ImpactPoint, BoxHalfSize, Orientation.Quaternion(), FColor::Red, false, 2.0f);
#endif
		}
		return true;
	}

	return false;
}

bool UAC_AttackManager::CheckCircleTypeAttack(const float In_Radius, const FVector& In_AttackPoint, TArray<FHitResult>& OutHits)
{
	ECollisionChannel TraceChannel = ECC_GameTraceChannel4;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(In_Radius);

	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		In_AttackPoint,
		In_AttackPoint,
		FQuat::Identity,
		TraceChannel,
		CollisionShape
	);

#if DEBUGMODE 
	FRotator DesiredAngleZ = m_OwnerCharacter->GetActorRotation();
	DrawCircle(GetWorld(), In_AttackPoint, 
		DesiredAngleZ.RotateVector(FVector(0, 1, 0)), DesiredAngleZ.RotateVector(FVector(0, 0, 1)), 
		FColor::Green, In_Radius, 50, false, 2.0f);
#endif

	if (bHit)
	{
		for (const FHitResult& OutHit : OutHits)
		{
#if DEBUGMODE 
			DesiredAngleZ = OutHit.GetActor()->GetActorRotation();
			DrawCircle(GetWorld(), In_AttackPoint,
				DesiredAngleZ.RotateVector(FVector(0, 1, 0)), DesiredAngleZ.RotateVector(FVector(0, 0, 1)),
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

//Box
bool UAC_AttackManager::CheckTheScopeOfTheBoxAttack(const FVector In_BoxHalfSize, const uint32 In_Range, TArray<FHitResult>& OutHits)
{
	const FVector Location	= m_OwnerCharacter->GetActorLocation();
	const FVector Forward	= m_OwnerCharacter->GetActorForwardVector();
	const FVector Start		= Location;
	const FVector End		= Location + Forward * In_BoxHalfSize.X;

	const FVector BoxHalfSize = In_BoxHalfSize;
	const FRotator Orientation = m_OwnerCharacter->GetActorRotation();

	ECollisionChannel TraceChannel = ECC_GameTraceChannel4;

	FCollisionQueryParams Params;
	
	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		Start,
		End,
		Orientation.Quaternion(),
		TraceChannel,
		FCollisionShape::MakeBox(BoxHalfSize),
		Params
	);

	UE_LOG(LogTemp, Warning, TEXT("start : %s  End : %s"), *Start.ToString(),*End.ToString());

	FVector draw(Start.X+(End.X - Start.X)/2, Start.Y+(End.Y - Start.Y)/2, Start.Z);

	DrawDebugBox(GetWorld(), draw, BoxHalfSize, Orientation.Quaternion(), FColor::Green, false, 2.0f);
	//DrawDebugBox(GetWorld(), End, BoxHalfSize, Orientation.Quaternion(), FColor::Blue, false, 2.0f);

	if (bHit)
	{
		for (const FHitResult& OutHit : OutHits)
		{
			DrawDebugBox(GetWorld(), OutHit.ImpactPoint, BoxHalfSize, Orientation.Quaternion(), FColor::Red, false, 2.0f);
		}
		return true;
	}

	return false;
}

// Called every frame
void UAC_AttackManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

