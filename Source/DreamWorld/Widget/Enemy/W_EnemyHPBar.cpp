// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Enemy/W_EnemyHPBar.h"
#include "Components/ProgressBar.h"

void UW_EnemyHPBar::UpdateHPBar(float In_CurrentHp, float In_MaxHp)
{
	m_HPProgressBar->SetPercent(In_CurrentHp / In_MaxHp);
}

void UW_EnemyHPBar::NativeConstruct()
{
	Super::NativeConstruct();

}
