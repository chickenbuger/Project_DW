// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/HUD/HUD_Main.h"
#include "DreamWorld/FrameWork/Main/GM_Main.h"

#include "Blueprint/UserWidget.h"

AHUD_Main::AHUD_Main()
{
}

UUserWidget* AHUD_Main::GetWidgetFromName(const FString& In_WidgetName)
{
	const int32 findPos = m_WidgetNames.Find(In_WidgetName);
	if (findPos == INDEX_NONE) { return nullptr; }

	TObjectPtr<UUserWidget> findWidget = m_Widgets[findPos];
	if (nullptr == findWidget) { return nullptr; }

	return findWidget;
}

void AHUD_Main::ShowWidgetFromName(const FString& In_WidgetName)
{
	int32 number = INDEX_NONE;
	TObjectPtr<UUserWidget> widget = GetWidgetInfo(In_WidgetName, number);
	if (widget == nullptr || number == INDEX_NONE) { return; }

	if (m_UsingWidget[number] == false)
	{
		SelfHitTestInvisibleWidget(widget);
		m_UsingWidget[number] = true;
	}
}

void AHUD_Main::CleanWidgetFromName(const FString& In_WidgetName)
{
	int32 number = INDEX_NONE;
	TObjectPtr<UUserWidget> widget = GetWidgetInfo(In_WidgetName, number);
	if (widget == nullptr || number == INDEX_NONE) { return; }

	if (m_UsingWidget[number] == true)
	{
		CollapsedWidget(widget);
		m_UsingWidget[number] = false;
	}
}

UUserWidget* AHUD_Main::GetWidgetInfo(const FString& In_WidgetName, int32& Out_Number)
{
	const int32 findPos = m_WidgetNames.Find(In_WidgetName);
	if (INDEX_NONE == findPos) { return nullptr; }
	Out_Number = findPos;

	TObjectPtr<UUserWidget> findWidget = m_Widgets[findPos];
	if (nullptr == findWidget) { return nullptr; }

	return findWidget;
}

void AHUD_Main::CollapsedWidget(UUserWidget* In_Widget)
{
	if (nullptr == In_Widget)
	{
		return;
	}

	if (false == In_Widget->IsInViewport())
	{
		In_Widget->AddToPlayerScreen();
	}

	ESlateVisibility visible = In_Widget->GetVisibility();
	switch (visible)
	{
	case ESlateVisibility::Collapsed:
	case ESlateVisibility::Hidden:
		break;
	case ESlateVisibility::Visible:
		In_Widget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::HitTestInvisible:
		In_Widget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::SelfHitTestInvisible:
		In_Widget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	default:
		break;
	}
}

void AHUD_Main::SelfHitTestInvisibleWidget(UUserWidget* In_Widget)
{
	if (nullptr == In_Widget)
	{
		return;
	}

	if (false == In_Widget->IsInViewport())
	{
		In_Widget->AddToPlayerScreen();
	}

	ESlateVisibility visible = In_Widget->GetVisibility();
	switch (visible)
	{
	case ESlateVisibility::Visible:
	case ESlateVisibility::HitTestInvisible:
	case ESlateVisibility::SelfHitTestInvisible:
		break;
	case ESlateVisibility::Collapsed:
		In_Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case ESlateVisibility::Hidden:
		In_Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	default:
		break;
	}
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

	m_UsingWidget.Init(false, m_Widgets.Num());

	ShowWidgetFromName(TEXT("PlayerMain"));

	UE_LOG(LogTemp, Warning, TEXT("Hud Main %d"), m_UiWidgets.Num());
}

void AHUD_Main::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_WidgetNames.Empty();
	m_UsingWidget.Empty();

	for (UUserWidget* widget : m_Widgets)
	{
		widget->RemoveFromParent();
		widget = nullptr;
	}
	m_Widgets.Empty();
}

void AHUD_Main::DrawHUD()
{
}
