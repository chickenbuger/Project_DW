// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/GI_Main.h"
#include "DreamWorld/Enemy/EnemyDamageWidget.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
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
	TArray<uint8> ObjectBytes;
	if (SaveGameToMemory(SaveGameObject, ObjectBytes))
	{
		return SaveDataToSlot(ObjectBytes, SlotName, UserIndex);
	}
	return false;
	*/
	TArray<uint8> ObjectBytes;
	if (UGameplayStatics::SaveGameToMemory(SaveGameObject, ObjectBytes))
	{
		FString savepath = FString::Printf(TEXT("%sSaveGames/%s.sav"), *m_SavePath, *SlotName);
		return FFileHelper::SaveArrayToFile(ObjectBytes,*savepath);
	}

	return false;
}