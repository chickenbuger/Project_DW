// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/HUD/HUD_Login.h"

AHUD_Login::AHUD_Login()
{
}

void AHUD_Login::BeginPlay()
{
	Super::BeginPlay();
	/** TODO
	* 시작 UI 생성
	* 데이터 세이브 파일을 통하여 이미 세이브 파일이 존재하는지 확인 및 데이터 점검
	* 없음 -> 데이터 세이브 파일 생성
	* 있음 -> 기존의 데이터 불러오기 (캐릭터 선택 창)
	* 
	*/
}

void AHUD_Login::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);
}

void AHUD_Login::DrawHUD()
{
	Super::DrawHUD();
}
