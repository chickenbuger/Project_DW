// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EnemyHPBar.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS()
class DREAMWORLD_API UW_EnemyHPBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateHPBar(float In_CurrentHp, float In_MaxHp);

public:
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UProgressBar> m_HPProgressBar;
};
