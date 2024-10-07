// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Sav_CharacterNames.generated.h"

/**
 * Player�̸� ����(������ 3���� ����)
 * Index_PlayerName (int - fstring) 1,2,3�� ������ ����(���� ĳ���� �̸� ��Ī)
 * �̸��� ������� ������ ������ �˻� ����
 * bool IsExist�� ������� ������ �ִ��� ��ȯ
 * �Լ� 2���� ����
 * IsExistName - string ���� �����ϴ��� Ȯ��
 * IsExistIndex - �ش� index���� �����ϴ��� Ȯ��
 */

UCLASS(Blueprintable)
class DREAMWORLD_API USav_CharacterNames : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, FString> TotalPlayerNames;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsExist;

public:
	UFUNCTION(BlueprintCallable)
	bool IsExistName(const FString In_Name);
	UFUNCTION(BlueprintCallable)
	bool IsExistIndex(const int In_Index);
};
