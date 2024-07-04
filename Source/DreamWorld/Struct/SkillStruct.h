// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillStruct.generated.h"

/**
* Skill ID
* 
*/
USTRUCT()
struct FSkillData
{
	GENERATED_BODY()

public:
	FSkillData() : m_SkillID(-1), m_IsActive(false), m_SkillName(""), m_Description("") {}

public:
	UPROPERTY()
	uint32 m_SkillID;

	UPROPERTY()
	bool m_IsActive;

	UPROPERTY()
	FName m_SkillName;

	UPROPERTY()
	FName m_Description;
};

UCLASS()
class DREAMWORLD_API USkillStruct : public UObject
{
	GENERATED_BODY()
	
};
