// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerWeaponState : uint8
{
	None				UMETA(DisplayName = "None"),
	NoWeapon		UMETA(DisplayName = "NoWeapon"),
};

UCLASS()
class DREAMWORLD_API UPlayerEnum : public UObject
{
	GENERATED_BODY()
};
