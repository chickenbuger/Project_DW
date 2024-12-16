// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/PS_Main.h"

/** Actor Component */
#include "DreamWorld/FrameWork/ActorComponent/AC_PlayerAnimation.h"

APS_Main::APS_Main()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APS_Main::Init()
{
	m_PlayerAnimationManager = NewObject<UAC_PlayerAnimation>(this, UAC_PlayerAnimation::StaticClass());
	if (nullptr == m_PlayerAnimationManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState_Main :: AC_PlayerAnimation is NULL"));
		return;
	}

	m_PlayerAnimationManager->RegisterComponent();
	m_PlayerAnimationManager->SetOwnerCharacter(GetPawn());

	m_PlayerAnimationManager->Init();
}

void APS_Main::RequestBasicAttackAnimation()
{
	if (nullptr == m_PlayerAnimationManager) { return; }
	
	if (!PlayerMovable()) { return; }

	m_PlayerAnimationManager->RequestBasicAttack(m_WeaponState, m_AttackSpeed);
}

void APS_Main::RequestPlayerSkill(int32 In_SkillID)
{
	if (nullptr == m_PlayerAnimationManager) { return; }

	if (!PlayerMovable()) { return; }

	m_PlayerAnimationManager->RequestSkill(m_WeaponState, In_SkillID, m_AttackSpeed);
}

void APS_Main::EndAnimation()
{
	m_PlayerAnimationManager->AnimationFinish();
}

bool APS_Main::PlayerMovable()
{
	// 애니메이션이 사용이 가능하지 않은 경우
	if (!m_PlayerAnimationManager->AnimationCanUsing())
	{
		return false;
	}

	return true;
}
