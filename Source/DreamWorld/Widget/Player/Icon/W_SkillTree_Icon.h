// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SkillTree_Icon.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class DREAMWORLD_API UW_SkillTree_Icon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton>			m_Button_SkillTree;

private:
	UFUNCTION()
	void RequestOpenSkillTreeWidget();
};
