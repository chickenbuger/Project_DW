// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PlayerMain.generated.h"

/**
 * 
 */
class UW_PlayerMainInfo;
class UW_SkillWrapper;

UCLASS()
class DREAMWORLD_API UW_PlayerMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();

	void SetPlayerName(FString In_PlayerName);

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UW_PlayerMainInfo>	UW_PlayerMainInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UW_SkillWrapper>		UW_SkillWrapper;
};
