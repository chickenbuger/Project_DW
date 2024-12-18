// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Animation/Player/AI_Player.h"
#include "DreamWorld/FrameWork/Main/C_Main.h"

#include "GameFramework/PawnMovementComponent.h"

void UAI_Player::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_PlayerPawn = nullptr;
	m_Velocity = FVector::ZeroVector;
	m_Speed = 0.0f;

	//Get Player Pawn
	m_PlayerPawn = TryGetPawnOwner();
}

void UAI_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!m_PlayerPawn)
	{
		m_PlayerPawn = TryGetPawnOwner();
	}

	if (!m_PlayerPawn)
	{
		return;
	}

	//Speed & Velocity
	TObjectPtr<UPawnMovementComponent> PawnMovementComponent = m_PlayerPawn->GetMovementComponent();

	m_Velocity = PawnMovementComponent->Velocity;

	m_Speed = m_Velocity.Size2D();
}

void UAI_Player::AnimNotify_AttackTiming()
{
	if (nullptr == m_PlayerPawn) return;
	
	TObjectPtr<AC_Main> player = Cast<AC_Main>(m_PlayerPawn);
	if (nullptr == player) return;

	if (player->GetAttackTiming())
	{
		player->RequestAttackTimeOff();
		UE_LOG(LogTemp, Warning, TEXT("Attack Notify"));
		player->ReqeustAttackCheck();
	}
}
