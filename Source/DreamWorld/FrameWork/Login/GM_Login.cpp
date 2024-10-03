// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Login/GM_Login.h"
#include "DreamWorld/FrameWork/Main/GI_Main.h"

#include "AndroidPermissionFunctionLibrary.h"

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
	PATH = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::ProjectSavedDir()); //FString("C:/PROJECT_DW/Saved/");
	gameInstance->SetSavePath(PATH);
#else
	PATH = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::ProjectSavedDir());
	gameInstance->SetSavePath(PATH);

	//권한 요청
	TArray<FString> RequestPermissions;
	if (!UAndroidPermissionFunctionLibrary::CheckPermission("android.permission.READ_EXTERNAL_STORAGE"))
	{
		RequestPermissions.Add("android.permission.READ_EXTERNAL_STORAGE");
	}

	if (!UAndroidPermissionFunctionLibrary::CheckPermission("android.permission.WRITE_EXTERNAL_STORAGE"))
	{
		RequestPermissions.Add("android.permission.WRITE_EXTERNAL_STORAGE");
	}

	if (RequestPermissions.Num() > 0)
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions(RequestPermissions);
	}
#endif
}