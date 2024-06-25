// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/SkillTree/W_SkillTree.h"

#include "DreamWorld/Widget/HUD/HUD_Main.h"

#include "Components/Border.h"

void UW_SkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	m_Border_Exit->OnMouseButtonDownEvent.BindUFunction(this, FName("ExitButtonDownFunc"));
}

FEventReply UW_SkillTree::ExitButtonDownFunc(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	if (nullptr == GetOwningPlayer())
	{
		return FEventReply();
	}

	if (nullptr == GetOwningPlayer()->GetHUD())
	{
		return FEventReply();
	}

	TObjectPtr<AHUD_Main> hud = Cast<AHUD_Main>(GetOwningPlayer()->GetHUD());
	if (nullptr == hud)
	{
		return FEventReply();
	}

	hud->CleanWidgetFromName("SkillTree");

	return FEventReply();
}
