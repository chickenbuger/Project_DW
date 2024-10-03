// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Lobby/GM_Lobby.h"
#include "DreamWorld/FrameWork/Main/GI_Main.h"

#include "DreamWorld/SaveGame/Sav_CharacterNames.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"

AGM_Lobby::AGM_Lobby()
{
	m_Sav_CharacterNames = nullptr;

	m_PlayerSpawnTransform.Add(FTransform(FRotator(0.f, 180.f, 0.f), FVector(150.f, -250.f, -2310.f)));
	m_PlayerSpawnTransform.Add(FTransform(FRotator(0.f, 180.f, 0.f), FVector(150.f,		0.f, -2310.f)));
	m_PlayerSpawnTransform.Add(FTransform(FRotator(0.f, 180.f, 0.f), FVector(150.f,	250.f, -2310.f)));

	m_AppearCharacterClass = StaticLoadClass(ACharacter::StaticClass() , nullptr, TEXT("Blueprint'/Game/Framework/Lobby/BC_AppearCharacter.BC_AppearCharacter_C'"));
	if (m_AppearCharacterClass ==nullptr)
	{
		return;
	}
}

void AGM_Lobby::Request_Save_CharacterName()
{
	/**
	* 캐릭터 슬롯 불러와서 저장하기
	* 
	*/
	 TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());
	 if (nullptr == gameinstance)
	 {
		 return;
	 }

	if (gameinstance->DoesSaveGameExistCustom(TotalCharacterSlotString, 0))
	{
		gameinstance->SaveGameToSlotCustom(m_Sav_CharacterNames, TotalCharacterSlotString, 0);
	}
	else
	{
		m_Sav_CharacterNames = Cast<USav_CharacterNames>(UGameplayStatics::CreateSaveGameObject(USav_CharacterNames::StaticClass()));
		gameinstance->SaveGameToSlotCustom(m_Sav_CharacterNames, TotalCharacterSlotString, 0);
	}
}

ACharacter* AGM_Lobby::Request_Create_Character(const int In_Pos)
{
	TObjectPtr<ACharacter> character = GetWorld()->SpawnActor<ACharacter>(m_AppearCharacterClass, m_PlayerSpawnTransform[In_Pos]);
	return character;
}

bool AGM_Lobby::Request_Add_NewPlayer_In_SaveData(const FString In_Name, const int In_Pos, FString& OuterResult)
{
	/**
	* Sav 데이터가 존재해야함(모든 캐릭터 이름을 가진 세이브 파일)
	* 파일 안에 생성하려는 캐릭터의 이름이 있어서는 안됨
	* 세이브 파일에 이름이 없다면 해당 파일의 이름으로 세이브 파일을 생성하기 때문에 저장 경로에 해당 이름의 세이브 파일을 확인
	* 만약에 세이브 파일이 있다면? -> 제거
	* 
	* 세이브 파일 생성(해당 캐릭터 이름.sav)
	*/
	OuterResult = "";

	if (!m_Sav_CharacterNames)
	{
		OuterResult = "111";
		return false;
	}

	if (m_Sav_CharacterNames->IsExistName(In_Name))
	{
		OuterResult = "222";
		return false;
	}

	TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());
	if (nullptr == gameinstance)
	{
		OuterResult = "333";
		return false;
	}
	
	if (gameinstance->DoesSaveGameExistCustom(In_Name, 0))
	{
		if (!gameinstance->DeleteSaveGameSlotCustom(In_Name, 0))
		{
			OuterResult = "444";
			return false;
		}
	}

	m_Sav_CharacterNames->TotalPlayerNames.Add(In_Pos, In_Name);
	gameinstance->SaveGameToSlotCustom(m_Sav_CharacterNames, In_Name, 0);

	return true;
}

void AGM_Lobby::BeginPlay()
{
	TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());
	if (nullptr == gameinstance)
	{
		return;
	}
	//슬롯 데이터 확인
	if (gameinstance->DoesSaveGameExistCustom(TotalCharacterSlotString, 0))
	{
		UE_LOG(LogTemp, Log, TEXT("AGM_Lobby::Load Data"));

		m_Sav_CharacterNames = Cast<USav_CharacterNames>(gameinstance->LoadGameFromSlotCustom(TotalCharacterSlotString, 0));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AGM_Lobby::Create Data"));

		m_Sav_CharacterNames = Cast<USav_CharacterNames>(UGameplayStatics::CreateSaveGameObject(USav_CharacterNames::StaticClass()));
		gameinstance->SaveGameToSlotCustom(m_Sav_CharacterNames, TotalCharacterSlotString, 0);
	}
}