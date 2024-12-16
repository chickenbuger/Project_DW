// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Main.generated.h"

/**
 * 
 */
class	AEnemyDamageWidget;
class	USaveGame;
class	UDataTable;
struct	FSkillData;

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
	/* ������ ���� ó�� */

	/**
	* ������ Widget�� ��ȯ
	* Widget�� �����ϴ� �迭�� ������� ��� SpawnActor�� ���� Object�� ���� �� ��ȯ
	*/
	TObjectPtr<AEnemyDamageWidget> RequestDamageIndicator();

	/**
	* ������ �ε�����͸� �迭�� ��ȯ
	*/
	void ReturnDamageIndicator(TObjectPtr<AEnemyDamageWidget> In_Object);



	/* ������ ���� ���� ó�� */

	/**
	* SaveGame�� ���Ͽ� ������ ����
	*/
	UFUNCTION(BlueprintCallable)
	bool SaveGameToSlotCustom(USaveGame* SaveGameObject, const FString& SlotName, const int32 UserIndex);

	/**
	* ������ �̸��� SaveGame ������ �����ϴ��� Ȯ��
	*/
	UFUNCTION(BlueprintCallable)
	bool DoesSaveGameExistCustom(const FString& SlotName, const int32 UserIndex);

	/**
	* �����ϴ� ���̺� ���� ����
	*/
	UFUNCTION(BlueprintCallable)
	bool DeleteSaveGameSlotCustom(const FString& SlotName, const int32 UserIndex);

	/**
	* ������ ���̺� ���� �ҷ�����
	*/
	UFUNCTION(BlueprintCallable)
	USaveGame* LoadGameFromSlotCustom(const FString& SlotName, const  int32 UserIndex);

	/* ������ ���̺� �������� */
	FSkillData* LoadSkillDataTable(int In_Code);

public:
	/* ������ ���̺� ���� Template */
	template<typename T>
	T* LoadGameFromSlotTemp(const FString& SlotName, const  int32 UserIndex);

private:
	/* ������ ���� */
	//������ ���� Ǯ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AEnemyDamageWidget>> m_DamageIndicatorWidgetPooling;

	//������ ���� Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_DamageIndicatorClass;

	/* �÷��̾� �̸� */
	//ĳ���� �̸� ����(���� ������ ������ ã�µ� ���)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString m_PlayerName;

	/* Save Game ������ ���� ��� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString m_SavePath;

	/* Data Table */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable>	m_DT_Skill;
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