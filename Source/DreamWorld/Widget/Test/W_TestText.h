// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_TestText.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class DREAMWORLD_API UW_TestText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetTestText(FString In_TestText);

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock> TB_TestText;
};
