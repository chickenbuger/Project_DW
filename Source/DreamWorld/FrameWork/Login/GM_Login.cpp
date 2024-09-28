// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Login/GM_Login.h"
#include "DreamWorld/FrameWork/Main/GI_Main.h"

#include "Kismet/KismetSystemLibrary.h"

AGM_Login::AGM_Login()
{
}

void AGM_Login::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UGI_Main> gameInstance = Cast<UGI_Main>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return;
	}

#if PLATFORM_WINDOWS
	PATH = FString("C:/PROJECT_DW/Saved/");
	gameInstance->SetSavePath(PATH);
#elif PLATFORM_ANDROID
	PATH = FString("/storage/Android/data/com.Jinsoo.BossArena/files/UnrealGame/DreamWorld/DreamWorld/Saved/");
	gameInstance->SetSavePath(PATH);

#endif
}