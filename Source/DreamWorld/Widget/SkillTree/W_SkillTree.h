// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SkillTree.generated.h"

/**
 * 
 */
class UWidgetSwitcher;
class UBorder;

UCLASS()
class DREAMWORLD_API UW_SkillTree : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UBorder>	m_Border_Exit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UWidgetSwitcher> m_WidgetSwitcher_L;

private:
	UFUNCTION()
	FEventReply ExitButtonDownFunc(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
};