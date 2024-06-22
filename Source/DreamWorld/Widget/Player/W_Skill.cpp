// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Player/W_Skill.h"

/** Controller */
#include "DreamWorld/FrameWork/Main/PC_Main.h"

#include "Components/Border.h"

void UW_Skill::RequestUsingSkillToPlayer() const
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

	/** Border에 Event 바인딩 */
	m_Border_Skill->OnMouseButtonDownEvent.BindUFunction(this, FName("MouseButtonDownFunc"));
	//m_Border_Skill->OnMouseButtonUpEvent.BindUFunction(this, FName("MouseButtonOnFunc"));

	//Init
	m_Skill_ID = -1;
}

FEventReply UW_Skill::MouseButtonDownFunc(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Check Calling MouseButtonDownFunc"));

	return FEventReply();
}

FEventReply UW_Skill::MouseButtonOnFunc(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Check Calling MouseButtonOnFunc"));

	return FEventReply();
}