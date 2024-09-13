// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PlayerMainInfo.generated.h"

/**
 * 
 */
class UTextBlock;
class UProgressBar;

UCLASS()
class DREAMWORLD_API UW_PlayerMainInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const FString In_PlayerName);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock>		m_TextBlock_PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UProgressBar>	m_ProgressBar_Hp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UProgressBar>	m_ProgressBar_Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UProgressBar>	m_ProgressBar_Stamina;

private:
	UFUNCTION()
	void DetectedChangeHp();
	
	UFUNCTION()
	void DetectedChangeMp();

	UFUNCTION()
	void DetectedChangeStamina();
};
