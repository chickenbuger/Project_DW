// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/HUD/HUD_Login.h"
#include "Blueprint/UserWidget.h"

AHUD_Login::AHUD_Login()
{
}

void AHUD_Login::BeginPlay()
{
	Super::BeginPlay();
	/** TODO
	* ���� UI ����
	* ������ ���̺� ������ ���Ͽ� �̹� ���̺� ������ �����ϴ��� Ȯ�� �� ������ ����
	* ���� -> ������ ���̺� ���� ����
	* ���� -> ������ ������ �ҷ����� (ĳ���� ���� â)
	* 
	*/
	//�α��� ���� ����
	TObjectPtr<UUserWidget> loginwidget = CreateWidget<UUserWidget>(GetWorld(), m_LoginWidget);
	if (nullptr == loginwidget) return;

	//���� �߰�
	loginwidget->AddToViewport();

	m_UsingWidgets.Add(loginwidget);
}

void AHUD_Login::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);

	for (auto& widget : m_UsingWidgets)
	{
		if (widget)
		{
			widget->RemoveFromParent();
			widget = nullptr;
		}
	}
	m_UsingWidgets.Empty();
}

void AHUD_Login::DrawHUD()
{
	Super::DrawHUD();
}
