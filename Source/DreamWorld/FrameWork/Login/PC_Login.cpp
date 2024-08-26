// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Login/PC_Login.h"

APC_Login::APC_Login()
{

}

void APC_Login::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("LOGIN PC : BeginPlay"));
	SetVirtualJoystickVisibility(false);
}