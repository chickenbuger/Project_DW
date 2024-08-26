// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Login/PC_Login.h"

APC_Login::APC_Login()
{

}

void APC_Login::BeginPlay()
{
	Super::BeginPlay();

	//로그인에서 조이스틱 비 활성화
	SetVirtualJoystickVisibility(false);
}