// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Player/Icon/W_SkillTree_Icon.h"
#include "DreamWorld/Widget/HUD/HUD_Main.h"

#include "Components/Button.h"

void UW_SkillTree_Icon::NativeConstruct()
{
	Super::NativeConstruct();

	m_Button_SkillTree->OnClicked.AddDynamic(this, &UW_SkillTree_Icon::RequestOpenSkillTreeWidget);
}

void UW_SkillTree_Icon::RequestOpenSkillTreeWidget()
{
	if (nullptr == GetOwningPlayer())							{ return; }
	if (nullptr == GetOwningPlayer()->GetHUD())		{ return; }

	TObjectPtr<AHUD_Main> hud = Cast<AHUD_Main>(GetOwningPlayer()->GetHUD());
	if (nullptr == hud) { return; }

	hud->ShowWidgetFromName(TEXT("SkillTree"));
}
