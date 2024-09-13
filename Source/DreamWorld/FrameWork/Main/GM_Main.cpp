// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/GM_Main.h"
#include "DreamWorld/FrameWork/Main/GI_Main.h"
#include "DreamWorld/FrameWork/Main/PS_Main.h"

#include "DreamWorld/Widget/HUD/HUD_Main.h"
#include "DreamWorld/Widget/Player/W_PlayerMain.h"

#include "Kismet/GameplayStatics.h"

void AGM_Main::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());

	TObjectPtr<APlayerController> controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TObjectPtr<APS_Main> playerstate =  controller->GetPlayerState<APS_Main>();

	const FName name = FName(*(gameinstance->GetPlayerName()));
	playerstate->SetCharacterName(name);

	/*
	TObjectPtr<AHUD_Main> hud = controller->GetHUD<AHUD_Main>();
	TObjectPtr<UUserWidget> widget = hud->GetWidgetFromName("PlayerMain");
	TObjectPtr<UW_PlayerMain> playermainwidget = Cast<UW_PlayerMain>(widget);

	playermainwidget->SetPlayerName(gameinstance->GetPlayerName());
	*/
}
