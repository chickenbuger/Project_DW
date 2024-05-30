// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Animation/Player/AI_Player.h"

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
