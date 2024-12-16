// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/GI_Main.h"
#include "DreamWorld/Enemy/EnemyDamageWidget.h"
#include "DreamWorld/SaveGame/Sav_CharacterNames.h"
#include "DreamWorld/Struct/SkillStruct.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFileManager.h"

#include "Kismet/GameplayStatics.h"

UGI_Main::UGI_Main()
{
	static ConstructorHelpers::FClassFinder<AActor> DamageIndicatorRef = TEXT("Blueprint'/Game/Character/Enemy/BA_EnemyDamageWidget.BA_EnemyDamageWidget_C'");
	if (DamageIndicatorRef.Class)
	{
		m_DamageIndicatorClass = DamageIndicatorRef.Class;
	}
}

TObjectPtr<AEnemyDamageWidget> UGI_Main::RequestDamageIndicator()
{
	if (m_DamageIndicatorWidgetPooling.IsEmpty())
	{
		//Pooling된 Object 없음 -> 추가
		TObjectPtr<AEnemyDamageWidget> PoolableObject = GetWorld()->SpawnActor<AEnemyDamageWidget>(m_DamageIndicatorClass, FVector().ZeroVector, FRotator().ZeroRotator);
		return PoolableObject;
	}
	
	return m_DamageIndicatorWidgetPooling.Pop();
}

void UGI_Main::ReturnDamageIndicator(TObjectPtr<AEnemyDamageWidget> In_Object)
{
	if (nullptr == In_Object) return;
	m_DamageIndicatorWidgetPooling.Push(In_Object);
}

bool UGI_Main::SaveGameToSlotCustom(USaveGame* SaveGameObject, const FString& SlotName, const int32 UserIndex)
{
	/*
		저장 Path에 파일 생성 및 저장
		메모리 공간 확보 및 바이트로 저장 -> 저장된 바이트를 해당 경로에 저장 
	*/
	TArray<uint8> ObjectBytes;
	if (UGameplayStatics::SaveGameToMemory(SaveGameObject, ObjectBytes))
	{
		FString savepath = FString::Printf(TEXT("%sSaveGames/%s.sav"), *m_SavePath, *SlotName);
		return FFileHelper::SaveArrayToFile(ObjectBytes,*savepath);
	}

	return false;
}

bool UGI_Main::DoesSaveGameExistCustom(const FString& SlotName, const int32 UserIndex)
{
	FString slotpath = FString::Printf(TEXT("%sSaveGames/%s.sav"), *m_SavePath, *SlotName);

	UE_LOG(LogTemp, Warning, TEXT("UGI_Main DoesSaveGameExistCustom"));

	if (IFileManager::Get().FileSize(*slotpath) >= 0)
	{
		return true;
	}
	
	return false;
}

bool UGI_Main::DeleteSaveGameSlotCustom(const FString& SlotName, const int32 UserIndex)
{
	FString deleteslotpath = FString::Printf(TEXT("%sSaveGames/%s.sav"), *m_SavePath, *SlotName);

	return IFileManager::Get().Delete(*deleteslotpath, true, false, true);
}

USaveGame* UGI_Main::LoadGameFromSlotCustom(const FString& SlotName, const int32 UserIndex)
{
	TArray<uint8> ObjectBytes;
	
	FString loadslotpath = FString::Printf(TEXT("%sSaveGames/%s.sav"), *m_SavePath, *SlotName);

	UE_LOG(LogTemp, Warning, TEXT("UGI_Main LoadGameFromSlotCustom"));

	if (SlotName.Len() > 0)
	{
		if (FFileHelper::LoadFileToArray(ObjectBytes, *loadslotpath))
		{
			return UGameplayStatics::LoadGameFromMemory(ObjectBytes);
		}
		else
		{
			ObjectBytes.Reset();
		}
	}

	return nullptr;
}

FSkillData* UGI_Main::LoadSkillDataTable(int In_Code)
{
	if (nullptr == m_DT_Skill) return nullptr;

	return m_DT_Skill->FindRow<FSkillData>(*FString::FromInt(In_Code),TEXT(""));
}
