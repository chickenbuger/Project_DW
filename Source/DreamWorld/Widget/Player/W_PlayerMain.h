// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PlayerMain.generated.h"

/**
 * 
 */
UCLASS()
class DREAMWORLD_API UW_PlayerMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
