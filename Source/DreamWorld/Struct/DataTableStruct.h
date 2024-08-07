// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "DataTableStruct.generated.h"

/**
 * 
 */
USTRUCT()
struct FUIMessage : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUIMessage() : m_MessageIndex(-1), m_Color_R(1.0f), m_Color_G(1.0f), m_Color_B(1.0f), m_Color_A(1.0f), m_MessageContent("") {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int		m_MessageIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float		m_Color_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float		m_Color_G;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float		m_Color_B;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float		m_Color_A;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_MessageContent;
};

UCLASS()
class DREAMWORLD_API UDataTableStruct : public UObject
{
	GENERATED_BODY()
	
};
