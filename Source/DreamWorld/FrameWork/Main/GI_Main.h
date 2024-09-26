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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AEnemyDamageWidget>> m_DamageIndicatorWidgetPooling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_DamageIndicatorClass;

	//캐릭터 이름 지정(남은 데이터 파일을 찾는데 사용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString m_PlayerName;

	UPROPERTY()
	FString m_SavePath;
};