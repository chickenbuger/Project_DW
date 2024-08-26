// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Login.generated.h"

/**
 * 
 */
UCLASS()
class DREAMWORLD_API APC_Login : public APlayerController
{
	GENERATED_BODY()

public:
	APC_Login();

protected:
	virtual void BeginPlay();
};
