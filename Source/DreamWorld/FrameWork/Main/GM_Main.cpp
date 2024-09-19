// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/GM_Main.h"
#include "DreamWorld/FrameWork/Main/GI_Main.h"
#include "DreamWorld/FrameWork/Main/PS_Main.h"

#include "Kismet/GameplayStatics.h"

void AGM_Main::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());

	TObjectPtr<APlayerController> controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TObjectPtr<APS_Main> playerstate =  controller->GetPlayerState<APS_Main>();

	const FName name = FName(*(gameinstance->GetPlayerName()));
	playerstate->SetCharacterName(name);
}
