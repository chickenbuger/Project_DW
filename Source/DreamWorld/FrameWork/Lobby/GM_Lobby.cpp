// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Lobby/GM_Lobby.h"
#include "DreamWorld/FrameWork/Main/GI_Main.h"

#include "DreamWorld/SaveGame/Sav_CharacterNames.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"

#include "DreamWorld/Widget/Test/W_TestText.h"

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

void AGM_Lobby::Testprint(FString str, int data)
{
	UE_LOG(LogTemp, Warning, TEXT("AGM_TestPrint"));
	TObjectPtr<UW_TestText> widget = Cast<UW_TestText>(CreateWidget<UUserWidget>(GetWorld(), TestWidget));
	widget->SetTestText(str + FString::Printf(TEXT(" %d"), data));
	widget->AddToViewport(1);
}

void AGM_Lobby::Request_Save_CharacterName()
{
	/**
	* ĳ���� ���� �ҷ��ͼ� �����ϱ�
	* 
	*/
	 TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());
	 if (nullptr == gameinstance)
	 {
		 return;
	 }

	 Testprint("Request_Save_CharacterName", 21);

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
	Testprint("Request_Create_Character", 20);
	Testprint(FString::Printf(TEXT("loc %.1f %.1f %.1f"), m_PlayerSpawnTransform[In_Pos].GetLocation().X, m_PlayerSpawnTransform[In_Pos].GetLocation().Y, m_PlayerSpawnTransform[In_Pos].GetLocation().Z),20);
	return character;
}

bool AGM_Lobby::Request_Add_NewPlayer_In_SaveData(const FString In_Name, const int In_Pos)
{
	/**
	* Sav �����Ͱ� �����ؾ���(��� ĳ���� �̸��� ���� ���̺� ����)
	* ���� �ȿ� �����Ϸ��� ĳ������ �̸��� �־�� �ȵ�
	* ���̺� ���Ͽ� �̸��� ���ٸ� �ش� ������ �̸����� ���̺� ������ �����ϱ� ������ ���� ��ο� �ش� �̸��� ���̺� ������ Ȯ��
	* ���࿡ ���̺� ������ �ִٸ�? -> ����
	* 
	* ���̺� ���� ����(�ش� ĳ���� �̸�.sav)
	*/

	if (!m_Sav_CharacterNames)
	{
		return false;
	}

	if (m_Sav_CharacterNames->IsExistName(In_Name))
	{
		return false;
	}

	TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());
	if (nullptr == gameinstance)
	{
		return false;
	}
	
	if (gameinstance->DoesSaveGameExistCustom(In_Name, 0))
	{
		if (!gameinstance->DeleteSaveGameSlotCustom(In_Name, 0))
		{
			return false;
		}
	}

	m_Sav_CharacterNames->TotalPlayerNames.Add(In_Pos, In_Name);
	gameinstance->SaveGameToSlotCustom(m_Sav_CharacterNames, In_Name, 0);

	return true;
}

void AGM_Lobby::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UGI_Main> gameinstance = Cast<UGI_Main>(GetGameInstance());
	if (nullptr == gameinstance)
	{
		return;
	}

	//���� ������ Ȯ��
	if (gameinstance->DoesSaveGameExistCustom(TotalCharacterSlotString, 0))
	{

		UE_LOG(LogTemp, Log, TEXT("AGM_Lobby::Load Data"));
		m_Sav_CharacterNames = gameinstance->LoadGameFromSlotTemp<USav_CharacterNames>(TotalCharacterSlotString, 0);

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AGM_Lobby::Create Data"));

		m_Sav_CharacterNames = Cast<USav_CharacterNames>(UGameplayStatics::CreateSaveGameObject(USav_CharacterNames::StaticClass()));
		gameinstance->SaveGameToSlotCustom(m_Sav_CharacterNames, TotalCharacterSlotString, 0);
	}
}