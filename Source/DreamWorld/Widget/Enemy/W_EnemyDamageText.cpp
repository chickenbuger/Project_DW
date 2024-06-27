// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Enemy/W_EnemyDamageText.h"
#include "Components/TextBlock.h"

void UW_EnemyDamageText::NativeConstruct()
{
	Super::NativeConstruct();
}

void UW_EnemyDamageText::SetDamage(const float In_Damage)
{
	m_Text_Damage->SetText(FText::FromString(FString::SanitizeFloat(In_Damage,0)));
}
