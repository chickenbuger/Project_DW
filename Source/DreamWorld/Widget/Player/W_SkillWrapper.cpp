// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Player/W_SkillWrapper.h"
#include "DreamWorld/Widget/Player/W_Skill.h"

void UW_SkillWrapper::NativeConstruct()
{
	Super::NativeConstruct();

	UW_Skill_Slot1->SetSkillID(0);
	UW_Skill_Slot2->SetSkillID(1);
}

void UW_SkillWrapper::ResetSkillSlotID()
{
	UW_Skill_Slot1->SetSkillID(-1);
	UW_Skill_Slot2->SetSkillID(-1);
	UW_Skill_Slot3->SetSkillID(-1);
	UW_Skill_Slot4->SetSkillID(-1);
	UW_Skill_Slot5->SetSkillID(-1);
}
