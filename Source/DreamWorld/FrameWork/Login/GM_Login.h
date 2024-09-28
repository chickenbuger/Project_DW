// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Login.generated.h"

/**
 * 
 */
UCLASS()
class DREAMWORLD_API AGM_Login : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_Login();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PATH;
	
protected:
	virtual void BeginPlay();
};
