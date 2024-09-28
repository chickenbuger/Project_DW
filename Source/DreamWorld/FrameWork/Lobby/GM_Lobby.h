// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Lobby.generated.h"

/**
 * 
 */
class USav_CharacterNames;

UCLASS()
class DREAMWORLD_API AGM_Lobby : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGM_Lobby();

public:
	//전체 캐릭터 이름이 포함된 세이브 파일 저장
	UFUNCTION(BlueprintCallable)
	void Request_Save_CharacterName();

	//캐릭터 생성(월드)
	UFUNCTION(BlueprintCallable)
	ACharacter* Request_Create_Character(const int In_Pos);


	UFUNCTION(BlueprintCallable)
	bool Request_Add_NewPlayer_In_SaveData(const FString In_Name, const int In_Pos);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USav_CharacterNames> m_Sav_CharacterNames;

protected:
	virtual void BeginPlay();

private:
	TArray<FTransform> m_PlayerSpawnTransform;

	UPROPERTY()
	TObjectPtr<UClass> m_AppearCharacterClass;

	const FString TotalCharacterSlotString = "CharactersSlot";
};