// Fill out your copyright notice in the Description page of Project Settings.

#include "DreamWorld/Widget/Player/W_PlayerMain.h"
#include "DreamWorld/Widget/Player/W_PlayerMainInfo.h"
#include "DreamWorld/Widget/Player/W_SkillWrapper.h"

void UW_PlayerMain::Init()
{
}

void UW_PlayerMain::SetPlayerName(FString In_PlayerName)
{
	if (UW_PlayerMainInfo)
	{
		UW_PlayerMainInfo->SetPlayerName(In_PlayerName);
	}
}

void UW_PlayerMain::NativeConstruct()
{
	Super::NativeConstruct();
}
