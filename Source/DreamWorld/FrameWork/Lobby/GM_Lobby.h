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
	UFUNCTION(BlueprintCallable)
	void Request_Save_CharacterName();

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
};

/*
private:
	UFUNCTION()
	void SaveCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UFUNCTION()
	void NewPlayerSaveCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UFUNCTION()
	void LoadCompleted(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);
	*/