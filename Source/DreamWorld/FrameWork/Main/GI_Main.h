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
	/* 데미지 위젯 처리 */

	/**
	* 데미지 Widget을 반환
	* Widget을 저장하는 배열이 비어있을 경우 SpawnActor를 통해 Object를 생성 후 반환
	*/
	TObjectPtr<AEnemyDamageWidget> RequestDamageIndicator();

	/**
	* 데미지 인디게이터를 배열로 반환
	*/
	void ReturnDamageIndicator(TObjectPtr<AEnemyDamageWidget> In_Object);



	/* 데이터 저장 관련 처리 */

	/**
	* SaveGame을 통하여 데이터 저장
	*/
	UFUNCTION(BlueprintCallable)
	bool SaveGameToSlotCustom(USaveGame* SaveGameObject, const FString& SlotName, const int32 UserIndex);

	/**
	* 동일한 이름의 SaveGame 파일이 존재하는지 확인
	*/
	UFUNCTION(BlueprintCallable)
	bool DoesSaveGameExistCustom(const FString& SlotName, const int32 UserIndex);

	/**
	* 존재하는 세이브 파일 제거
	*/
	UFUNCTION(BlueprintCallable)
	bool DeleteSaveGameSlotCustom(const FString& SlotName, const int32 UserIndex);

	/**
	* 데이터 세이브 파일 불러오기
	*/
	UFUNCTION(BlueprintCallable)
	USaveGame* LoadGameFromSlotCustom(const FString& SlotName, const  int32 UserIndex);

	/* 데이터 테이블 가져오기 */
	FSkillData* LoadSkillDataTable(int In_Code);

public:
	/* 데이터 세이브 파일 Template */
	template<typename T>
	T* LoadGameFromSlotTemp(const FString& SlotName, const  int32 UserIndex);

private:
	/* 데미지 관련 */
	//데미지 위젯 풀링
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AEnemyDamageWidget>> m_DamageIndicatorWidgetPooling;

	//데미지 위젯 Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_DamageIndicatorClass;

	/* 플레이어 이름 */
	//캐릭터 이름 지정(남은 데이터 파일을 찾는데 사용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString m_PlayerName;

	/* Save Game 데이터 저장 경로 */
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