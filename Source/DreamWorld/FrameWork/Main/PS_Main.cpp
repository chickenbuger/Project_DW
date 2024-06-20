// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/PS_Main.h"

/** Actor Component */
#include "DreamWorld/FrameWork/ActorComponent/AC_SkillManager.h"
#include "DreamWorld/FrameWork/ActorComponent/AC_PlayerAnimation.h"

APS_Main::APS_Main()
{
	PrimaryActorTick.bCanEverTick = false;

	m_PlayerName = FName(TEXT("JS"));

	m_MaxHealth			= 100.0f;
	m_MaxMana				= 100.0f;
	m_MaxStamina		= 100.0f;
	m_Health					= 100.0f;
	m_Mana					= 100.0f;
	m_Stamina				= 100.0f;

	m_WeaponState = EPlayerWeaponState::NoWeapon;
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

void APS_Main::PlayerInfoWidgetInit()
{
	if ((Dele_Changed_Hp.IsBound()) && (Dele_Changed_Mana.IsBound()) && (Dele_Changed_Stamina.IsBound()))
	{
		Dele_Changed_Hp.Broadcast();
		Dele_Changed_Mana.Broadcast();
		Dele_Changed_Stamina.Broadcast();
	}
}

void APS_Main::RequestBasicAttackAnimation()
{
	if (nullptr == m_PlayerAnimationManager) { return; }

	if (!PlayerMoveable()) { return; }

	m_PlayerAnimationManager->RequestBasicAttack(m_WeaponState);
}

void APS_Main::RequestPlayerSkill(int32 In_SkillID)
{
	if (nullptr == m_PlayerAnimationManager) { return; }

	if (!PlayerMoveable()) { return; }

	m_PlayerAnimationManager->RequestSkill(m_WeaponState, In_SkillID);
}

void APS_Main::ReceiveDamage(float In_Damage)
{
	//데미지가 비정상적인지 확인
	if (0 > In_Damage) { return; }

	//데미지가 체력보다 높은지 확인
	if (In_Damage >= m_Health)
	{
		m_Health = 0;
	}

	m_Health -= In_Damage;
}

void APS_Main::EndAnimation()
{
	m_PlayerAnimationManager->AnimationFinish();
}

bool APS_Main::PlayerMoveable()
{
	// 애니메이션이 사용이 가능하지 않은 경우
	if (!m_PlayerAnimationManager->AnimationCanUsing())
	{
		return false;
	}

	return true;
}
