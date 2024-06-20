// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Player/W_PlayerMainInfo.h"

#include "DreamWorld/FrameWork/Main/PS_Main.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UW_PlayerMainInfo::NativeConstruct()
{
	Super::NativeConstruct();

	TObjectPtr<APS_Main> playerstate = GetOwningPlayer()->GetPlayerState<APS_Main>();
	if (nullptr == playerstate) { return; }

	m_TextBlock_PlayerName->SetText(FText::FromName(playerstate->GetCharacterName()));

	playerstate->Dele_Changed_Hp.AddUFunction(this, FName("DetectedChangeHp"));
	playerstate->Dele_Changed_Mana.AddUFunction(this, FName("DetectedChangeMp"));
	playerstate->Dele_Changed_Stamina.AddUFunction(this, FName("DetectedChangeStamina"));

	playerstate->PlayerInfoWidgetInit();
}

void UW_PlayerMainInfo::DetectedChangeHp()
{
	TObjectPtr<APS_Main> playerstate = GetOwningPlayer()->GetPlayerState<APS_Main>();
	if (nullptr == playerstate) { return; }

	const float maxhp = playerstate->GetMaxHealth();
	const float hp = playerstate->GetHealth();

	m_ProgressBar_Hp->SetPercent(hp / maxhp);
}

void UW_PlayerMainInfo::DetectedChangeMp()
{
	TObjectPtr<APS_Main> playerstate = GetOwningPlayer()->GetPlayerState<APS_Main>();
	if (nullptr == playerstate) { return; }

	const float maxmana = playerstate->GetMaxHealth();
	const float mana = playerstate->GetHealth();

	m_ProgressBar_Mana->SetPercent(mana / maxmana);
}

void UW_PlayerMainInfo::DetectedChangeStamina()
{
	TObjectPtr<APS_Main> playerstate = GetOwningPlayer()->GetPlayerState<APS_Main>();
	if (nullptr == playerstate) { return; }

	const float maxstamina = playerstate->GetMaxHealth();
	const float stamina = playerstate->GetHealth();

	m_ProgressBar_Stamina->SetPercent(stamina / maxstamina);
}
