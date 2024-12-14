// Fill out your copyright notice in the Description page of Project Settings.

/** Manager */
#include "DreamWorld/FrameWork/ActorComponent/AC_AttackManager.h"

/** Enemy */
#include "DreamWorld/Enemy/NC_EnemyBase.h"

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

// Called when the game starts
void UAC_AttackManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

//Box
bool UAC_AttackManager::CheckTheScopeOfTheBoxAttack(const FVector In_BoxHalfSize, const uint32 In_Range, TArray<FHitResult>& OutHits)
{
	const FVector Location= m_OwnerCharacter->GetActorLocation();
	const FVector Forward	= m_OwnerCharacter->GetActorForwardVector();
	const FVector Start		= Location + Forward * 100.f;
	const FVector End		= Start + Forward * In_Range;

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

