// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/PS_Main.h"
#include "DreamWorld/FrameWork/ActorComponent/AC_SkillManager.h"

APS_Main::APS_Main()
{
	m_Health		= 0.0f;
	m_Mana			= 0.0f;
	m_Stamina		= 0.0f;
}

void APS_Main::Init()
{
	m_SkillManager = NewObject<UAC_SkillManager>(this,UAC_SkillManager::StaticClass());
	if (nullptr == m_SkillManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState_Main :: SkillManger is NULL"));
		return;
	}
	m_SkillManager->RegisterComponent();

	m_SkillManager->Init();
}
