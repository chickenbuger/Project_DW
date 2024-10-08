// Fill out your copyright notice in the Description page of Project Settings.

#include "DreamWorld/Widget/Player/W_PlayerMain.h"
#include "DreamWorld/Widget/Player/W_PlayerMainInfo.h"
#include "DreamWorld/Widget/Player/W_SkillWrapper.h"

#include "DreamWorld/FrameWork/Main/GI_Main.h"

void UW_PlayerMain::Init()
{
	TObjectPtr<UGI_Main> gameInstance = Cast<UGI_Main>(GetGameInstance());
	if (nullptr == gameInstance) return; 

	//Info widget 이름 적용
	SetPlayerName(gameInstance->GetPlayerName());
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
