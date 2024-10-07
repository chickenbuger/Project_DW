// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Main.generated.h"

/**
 * 
 */
class AEnemyDamageWidget;
class USaveGame;

UCLASS()
class DREAMWORLD_API UGI_Main : public UGameInstance
{
	GENERATED_BODY()

public:
	UGI_Main();

public:
	//Getter
	FString GetPlayerName() const { return m_PlayerName; }
	FString GetSavePath() const { return m_SavePath; }

	//Setter
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const FString In_PlayerName) { m_PlayerName = In_PlayerName; }
	void SetSavePath(const FString In_SavePath) { m_SavePath = In_SavePath; }

public:
	TObjectPtr<AEnemyDamageWidget> RequestDamageIndicator();
	void ReturnDamageIndicator(TObjectPtr<AEnemyDamageWidget> In_Object);

	UFUNCTION(BlueprintCallable)
	bool SaveGameToSlotCustom(USaveGame* SaveGameObject, const FString& SlotName, const int32 UserIndex);

	UFUNCTION(BlueprintCallable)
	bool DoesSaveGameExistCustom(const FString& SlotName, const int32 UserIndex);

	UFUNCTION(BlueprintCallable)
	bool DeleteSaveGameSlotCustom(const FString& SlotName, const int32 UserIndex);

	UFUNCTION(BlueprintCallable)
	USaveGame* LoadGameFromSlotCustom(const FString& SlotName, const  int32 UserIndex);

public:
	template<typename T>
	T* LoadGameFromSlotTemp(const FString& SlotName, const  int32 UserIndex);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AEnemyDamageWidget>> m_DamageIndicatorWidgetPooling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_DamageIndicatorClass;

	//ĳ���� �̸� ����(���� ������ ������ ã�µ� ���)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString m_PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString m_SavePath;
};

template<typename T>
inline T* UGI_Main::LoadGameFromSlotTemp(const FString& SlotName, const int32 UserIndex)
{
	USaveGame* savegame = LoadGameFromSlotCustom(SlotName, UserIndex);
	return Cast<T>(savegame);
}

template<>
inline USaveGame* UGI_Main::LoadGameFromSlotTemp<USaveGame>(const FString& SlotName, const int32 UserIndex)
{
	USaveGame* savegame = LoadGameFromSlotCustom(SlotName, UserIndex);
	return savegame;
}