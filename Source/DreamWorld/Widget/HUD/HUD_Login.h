// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_Login.generated.h"

/**
 * 
 */
UCLASS()
class DREAMWORLD_API AHUD_Login : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_Login();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;
	virtual void DrawHUD() override;
};
