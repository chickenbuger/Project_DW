// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Player/W_Skill.h"

/** Controller */
#include "DreamWorld/FrameWork/Main/PC_Main.h"

void UW_Skill::RequestUsingSkillToPlayer()
{
	//check controller
	if (nullptr == GetOwningPlayer())
	{
		return;
	}

	TObjectPtr<APC_Main> Controller = Cast<APC_Main>(GetOwningPlayer());
	if(nullptr == Controller)
	{
		return;
	}

	Controller->RequestAttackToCharacter(m_Skill_ID);
}

void UW_Skill::NativeConstruct()
{
	Super::NativeConstruct();

	//Init
	m_Skill_ID = -1;
}