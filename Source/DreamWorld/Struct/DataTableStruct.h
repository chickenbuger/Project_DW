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

UENUM()
enum class ECharacterPartType : uint8
{
	E_NONE				UMETA(DisplayName = "None"),

	E_Helm				UMETA(DisplayName = "Helm"),
	E_Hair				UMETA(DisplayName = "Hair"),
	E_Face				UMETA(DisplayName = "Face"),
	E_Shoulder			UMETA(DisplayName = "Shoulder"),
	E_Cloth				UMETA(DisplayName = "Cloth"),
	E_Glove				UMETA(DisplayName = "Glove"),
	E_Belt				UMETA(DisplayName = "Belt"),
	E_Shoes				UMETA(DisplayName = "Shoes"),
};

USTRUCT()
struct FCharacterPartCode : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterPartCode() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterPartType	m_PartType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh*			m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName							m_Name;
};

UCLASS()
class DREAMWORLD_API UDataTableStruct : public UObject
{
	GENERATED_BODY()
	
};
