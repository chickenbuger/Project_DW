// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Player/W_Skill.h"

/** Character */
#include "DreamWorld/FrameWork/Main/C_Main.h"

void UW_Skill::RequestUsingSkillToPlayer()
{
	//check controller
	if (nullptr == GetOwningPlayer())
	{
		return;
	}

	//check controlling character
	if (nullptr == GetOwningPlayer()->GetCharacter())
	{
		return;
	}

	TObjectPtr<ACharacter> Character = GetOwningPlayer()->GetCharacter();
	if (nullptr == Character)
	{
		return;
	}

	TObjectPtr<AC_Main> ControllingCharacter = Cast<AC_Main>(Character);
	if(nullptr == ControllingCharacter)
	{
		return;
	}

	ControllingCharacter->RequestedAttack(m_Skill_ID);
}

void UW_Skill::NativeConstruct()
{
	Super::NativeConstruct();

	//Init
	m_Skill_ID = -1;

	UE_LOG(LogTemp, Warning, TEXT("Skill Init %d"),m_Skill_ID);
}