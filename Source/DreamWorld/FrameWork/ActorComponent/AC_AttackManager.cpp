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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAC_AttackManager::CallAttemptAttack(TObjectPtr<AActor> in_Player, float in_Damage)
{
	TArray<FHitResult> OutHits;

	if (!CheckTheScopeOfTheAttack(100.f, OutHits))
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

		enemy->TakeDamage(10.0f);
	}
}

// Called when the game starts
void UAC_AttackManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UAC_AttackManager::CheckTheScopeOfTheAttack(uint32 in_Range, TArray<FHitResult>& OutHits)
{
	FVector Location= m_OwnerCharacter->GetActorLocation();
	FVector Forward	= m_OwnerCharacter->GetActorForwardVector();
	FVector Start		= Location + Forward * 100.f;
	FVector End		= Start + Forward * in_Range;

	FVector BoxHalfSize = FVector(50.f, 50.f, 50.f);
	FRotator Orientation = m_OwnerCharacter->GetActorRotation();

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

	DrawDebugBox(GetWorld(), Start, BoxHalfSize, Orientation.Quaternion(), FColor::Green, false, 2.0f);
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

