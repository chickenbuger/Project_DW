// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/ParentPlayerState/PS_CharacterStatusDetail.h"

APS_CharacterStatusDetail::APS_CharacterStatusDetail()
{
	m_MaxHealth = 100.0f;
	m_MaxMana = 100.0f;
	m_MaxStamina = 100.0f;
	m_MaxAttackSpeed = 1.5f;

	m_Health = 100.0f;
	m_Mana = 100.0f;
	m_Stamina = 100.0f;
	m_AttackSpeed = 1.0f;

	m_WeaponState = EPlayerWeaponState::NoWeapon;
}

void APS_CharacterStatusDetail::PlayerInfoWidgetInit() const
{
	if ((Dele_Changed_Hp.IsBound()) && (Dele_Changed_Mana.IsBound()) && (Dele_Changed_Stamina.IsBound()))
	{
		Dele_Changed_Hp.Broadcast();
		Dele_Changed_Mana.Broadcast();
		Dele_Changed_Stamina.Broadcast();
	}
}

void APS_CharacterStatusDetail::ReceiveDamage(float In_Damage)
{
	//데미지가 비정상적인지 확인
	if (0 > In_Damage) { return; }

	//데미지가 체력보다 높은지 확인
	if (In_Damage >= m_Health)
	{
		m_Health = 0;
	}

	m_Health -= In_Damage;

	if (Dele_Changed_Hp.IsBound())
	{
		Dele_Changed_Hp.Broadcast();
	}
}

void APS_CharacterStatusDetail::UsingMana(const float In_Mana)
{
	if (!CanUseMana(In_Mana))
	{
		return;
	}

	m_Mana -= In_Mana;

	if (Dele_Changed_Mana.IsBound())
	{
		Dele_Changed_Mana.Broadcast();
	}
}

void APS_CharacterStatusDetail::UsingStamina(const float In_Stamina)
{
	if (!CanUseStamina(In_Stamina))
	{
		return;
	}

	m_Stamina -= In_Stamina;

	if (Dele_Changed_Stamina.IsBound())
	{
		Dele_Changed_Stamina.Broadcast();
	}
}

bool APS_CharacterStatusDetail::CanUseMana(const float In_Mana)
{
	if (In_Mana > m_Mana) { return false; }
	return true;
}

bool APS_CharacterStatusDetail::CanUseStamina(const float In_Stamina)
{
	if (In_Stamina > m_Stamina) { return false; }
	return true;
}
