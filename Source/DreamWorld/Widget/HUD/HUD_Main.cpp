// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/HUD/HUD_Main.h"
#include "DreamWorld/FrameWork/Main/GM_Main.h"

#include "Blueprint/UserWidget.h"

AHUD_Main::AHUD_Main()
{
}

UUserWidget* AHUD_Main::GetWidgetFromName(const FString& inWidgetName)
{
	return TObjectPtr<UUserWidget>();
}

void AHUD_Main::ShowWidgetFromName(const FString& inWidgetName)
{
}

void AHUD_Main::CleanWidgetFromName(const FString& inWidgetName)
{
}

void AHUD_Main::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hud Main BeginPlay"));

	TObjectPtr<AGameModeBase> gamemode = GetWorld()->GetAuthGameMode();
	if (nullptr == gamemode) { return; }

	TObjectPtr<AGM_Main> maingamemode = Cast<AGM_Main>(gamemode);
	if (nullptr == maingamemode) { return; }

	for(TSubclassOf<UUserWidget> widgetclass : m_UiWidgets)
	{
		//설정된 Widget 추가
		TObjectPtr<UUserWidget> newWidget = CreateWidget<UUserWidget>(GetWorld(), widgetclass);
		if (nullptr == newWidget) { return; }

		newWidget->AddToViewport();
		newWidget->SetVisibility(ESlateVisibility::Collapsed);
		m_Widgets.Add(newWidget);

		//Widget에 대한 이름 추가
		FString newWidgetName = newWidget->GetClass()->GetName();
		newWidgetName.RemoveAt(0, 3);
		newWidgetName.RemoveAt(newWidgetName.Len() - 2, newWidgetName.Len());
		m_WidgetNames.Add(newWidgetName);
	}

	UE_LOG(LogTemp, Warning, TEXT("Hud Main %d"), m_UiWidgets.Num());
}

void AHUD_Main::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AHUD_Main::DrawHUD()
{
}
