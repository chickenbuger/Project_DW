// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ENUM/PlayerEnum.h"
#include "Engine/DataTable.h"
#include "SkillStruct.generated.h"

/**
* Skill ID
* 
*/
USTRUCT()
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSkillData() : m_SkillID(-1), m_Attack_Type(), m_Attack_Range(), m_SkillName(""), m_Description("") {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int							m_SkillID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EAttackCheckType>	m_Attack_Type;

	/**
	* Box		: x,y,z
	* Circle	: R
	* Arc		: R, StartAngle, EndAngle
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector>				m_Attack_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName						m_SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName						m_Description;
};

UCLASS()
class DREAMWORLD_API USkillStruct : public UObject
{
	GENERATED_BODY()
	
};
