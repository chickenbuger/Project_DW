// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/PS_Main.h"

/** Actor Component */
#include "DreamWorld/FrameWork/ActorComponent/AC_SkillManager.h"
#include "DreamWorld/FrameWork/ActorComponent/AC_PlayerAnimation.h"

APS_Main::APS_Main()
{
	PrimaryActorTick.bCanEverTick = false;

	m_PlayerName = FName(TEXT("JS"));
}

void APS_Main::Init()
{
	m_SkillManager = NewObject<UAC_SkillManager>(this,UAC_SkillManager::StaticClass());
	if (nullptr == m_SkillManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState_Main :: SkillManger is NULL"));
		return;
	}
	//NewObject 이후에 무조건 필요, 생성된 컴포넌트를 활성화 하는데 필수
	m_SkillManager->RegisterComponent();
	m_SkillManager->SetOwnerCharacter(GetPawn());

	m_SkillManager->Init();

	m_PlayerAnimationManager = NewObject<UAC_PlayerAnimation>(this, UAC_PlayerAnimation::StaticClass());
	if (nullptr == m_SkillManager)
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
