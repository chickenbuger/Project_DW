// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/GM_Main.h"
#include "DreamWorld/Widget/HUD/HUD_Main.h"

#include "Kismet/GameplayStatics.h"

void AGM_Main::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 Hud Init
	TObjectPtr<APlayerController> controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->GetHUD<AHUD_Main>()->Init();
}
