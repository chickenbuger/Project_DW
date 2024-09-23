// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Lobby/GM_Lobby.h"

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
	if (UGameplayStatics::DoesSaveGameExist("CharactersSlot", 0))
	{
		FAsyncSaveGameToSlotDelegate delegate = FAsyncSaveGameToSlotDelegate::CreateUObject(this, &AGM_Lobby::SaveCompleted);

		m_Sav_CharacterNames = Cast<USav_CharacterNames>(UGameplayStatics::CreateSaveGameObject(USav_CharacterNames::StaticClass()));
		UGameplayStatics::AsyncSaveGameToSlot(m_Sav_CharacterNames, "CharactersSlot", 0, delegate);
	}
}

ACharacter* AGM_Lobby::Request_Create_Character(const int In_Pos)
{
	TObjectPtr<ACharacter> character =GetWorld()->SpawnActor<ACharacter>(m_AppearCharacterClass, m_PlayerSpawnTransform[In_Pos]);
	return character;
}

bool AGM_Lobby::Request_Add_NewPlayer_In_SaveData(const FString In_Name, const int In_Pos)
{
	if (!m_Sav_CharacterNames)
	{
		return false;
	}

	if (m_Sav_CharacterNames->IsExistName(In_Name))
	{
		return false;
	}

	if (UGameplayStatics::DoesSaveGameExist(In_Name, 0))
	{
		if (!UGameplayStatics::DeleteGameInSlot(In_Name, 0))
		{
			return false;
		}
	}

	m_NewPlayerPos = In_Pos;

	FAsyncSaveGameToSlotDelegate delegate = FAsyncSaveGameToSlotDelegate::CreateUObject(this, &AGM_Lobby::SaveCompleted);

	m_Sav_CharacterNames = Cast<USav_CharacterNames>(UGameplayStatics::CreateSaveGameObject(USav_CharacterNames::StaticClass()));
	UGameplayStatics::AsyncSaveGameToSlot(m_Sav_CharacterNames, In_Name, 0, delegate);

	return false;
}

void AGM_Lobby::BeginPlay()
{
	//슬롯 데이터 확인
	if (UGameplayStatics::DoesSaveGameExist("CharactersSlot", 0))
	{
		FAsyncLoadGameFromSlotDelegate delegate = FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &AGM_Lobby::LoadCompleted);

		UGameplayStatics::AsyncLoadGameFromSlot("CharactersSlot", 0, delegate);
	}
	else
	{
		FAsyncSaveGameToSlotDelegate delegate = FAsyncSaveGameToSlotDelegate::CreateUObject(this, &AGM_Lobby::SaveCompleted);

		m_Sav_CharacterNames = Cast<USav_CharacterNames>(UGameplayStatics::CreateSaveGameObject(USav_CharacterNames::StaticClass()));
		UGameplayStatics::AsyncSaveGameToSlot(m_Sav_CharacterNames, "CharactersSlot", 0, delegate);
	}
}

void AGM_Lobby::SaveCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	UE_LOG(LogTemp, Log, TEXT("AGM_Lobby::SaveCompleted() : [%s][%d][%d]"), *SlotName, UserIndex, bSuccess);

	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("success : AsyncSaveGameToSlot()"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("failed : AsyncSaveGameToSlot()"));
	}
}

void AGM_Lobby::NewPlayerSaveCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	UE_LOG(LogTemp, Log, TEXT("AGM_Lobby::NewPlayerSaveCompleted() : [%s][%d][%d]"), *SlotName, UserIndex, bSuccess);

	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("success : AsyncSaveGameToSlot()"));
		m_Sav_CharacterNames->TotalPlayerNames.Add(m_NewPlayerPos, SlotName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("failed : AsyncSaveGameToSlot()"));
	}
}

void AGM_Lobby::LoadCompleted(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	UE_LOG(LogTemp, Log, TEXT("UMyGameInstanceSubsystem::LoadCompleted() : [%s][%d]"), *SlotName, UserIndex);

	if (SaveGame)
	{
		TObjectPtr<USav_CharacterNames> data = Cast<USav_CharacterNames>(SaveGame);

		//ToDo : 데이터 저장
		m_Sav_CharacterNames = data;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("failed : AsyncLoadGameToSlot()"));
	}
}
