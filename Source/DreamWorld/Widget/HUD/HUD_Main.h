// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_Main.generated.h"

/**
 * 
 */

UCLASS()
class DREAMWORLD_API AHUD_Main : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_Main();

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UUserWidget>> m_UiWidgets;

public:
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void	ShowWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void	CleanWidgetFromName(const FString& inWidgetName);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void DrawHUD() override;

private:
	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> m_Widgets;

	UPROPERTY()
	TArray<FString> m_WidgetNames;
};
