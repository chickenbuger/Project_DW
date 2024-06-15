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
	//EX) Widget Name : BW_Main -> Param(Main)
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidgetFromName(const FString& In_WidgetName);

	UFUNCTION(BlueprintCallable)
	void	ShowWidgetFromName(const FString& In_WidgetName);

	UFUNCTION(BlueprintCallable)
	void	CleanWidgetFromName(const FString& In_WidgetName);

protected:
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidgetInfo(const FString& In_WidgetName, int32& Out_Number);

	UFUNCTION(BlueprintCallable)
	void	CollapsedWidget(UUserWidget* In_Widget);

	UFUNCTION(BlueprintCallable)
	void	SelfHitTestInvisibleWidget(UUserWidget* In_Widget);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void DrawHUD() override;

private:
	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>>		m_Widgets;

	UPROPERTY()
	TArray<FString>										m_WidgetNames;

	UPROPERTY()
	TArray<bool>											m_UsingWidget;
};
