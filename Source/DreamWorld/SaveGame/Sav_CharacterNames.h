// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Sav_CharacterNames.generated.h"

/**
 * Player이름 저장(슬롯은 3개가 존재)
 * Index_PlayerName (int - fstring) 1,2,3번 슬롯이 존재(각각 캐릭터 이름 매칭)
 * 이름을 기반으로 나머지 데이터 검색 예정
 * bool IsExist를 기반으로 데이터 있는지 반환
 * 함수 2개가 존재
 * IsExistName - string 값이 존재하는지 확인
 * IsExistIndex - 해당 index값이 존재하는지 확인
 */

UCLASS()
class DREAMWORLD_API USav_CharacterNames : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool IsExistName(const FString In_Name);
	UFUNCTION(BlueprintCallable)
	bool IsExistIndex(const int In_Index);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, FString> TotalPlayerNames;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsExist;
};
