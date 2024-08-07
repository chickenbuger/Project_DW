// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

/** Enum */
#include "../../ENUM/PlayerEnum.h"

#include "PS_CharacterStatusDetail.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnChanged_Hp);
DECLARE_MULTICAST_DELEGATE(FOnChanged_Mana);
DECLARE_MULTICAST_DELEGATE(FOnChanged_Stamina);

UCLASS()
class DREAMWORLD_API APS_CharacterStatusDetail : public APlayerState
{
	GENERATED_BODY()
	
public:
	APS_CharacterStatusDetail();

public:
	FOnChanged_Hp Dele_Changed_Hp;
	FOnChanged_Mana Dele_Changed_Mana;
	FOnChanged_Stamina Dele_Changed_Stamina;

public:
	//Getter
	float				GetMaxHealth() const			{ return m_MaxHealth; }
	float				GetMaxMana() const			{ return m_MaxMana; }
	float				GetMaxStamina() const		{ return m_MaxStamina; }
	float				GetHealth() const				{ return m_Health; }
	float				GetMana() const					{ return m_Mana; }
	float				GetStamina() const				{ return m_Stamina; }

	//Setter
	void				SetMaxMana(float In_MaxMana)				{ m_MaxMana = In_MaxMana; }
	void				SetMaxStamina(float In_MaxStamina)	{ m_MaxStamina = In_MaxStamina; }
	void				SetHealth(float In_Helath)						{ m_Health = In_Helath; }
	void				SetMana(float In_Mana)							{ m_Mana = In_Mana; }
	void				SetStamina(float In_Stamina)					{ m_Stamina = In_Stamina; }

public:
	//Init
	void PlayerInfoWidgetInit() const;

	//Take Damage
	void ReceiveDamage(float In_Damage);
	
	//Mana
	void UsingMana(const float In_Mana);

	//Stamina
	void UsingStamina(const float In_Stamina);

protected:
	/** Max */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_MaxMana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_MaxAttackSpeed;

	/** Current */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_AttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	EPlayerWeaponState m_WeaponState;

protected:
	//Mana
	bool CanUseMana(const float In_Mana);

	//Stamina
	bool CanUseStamina(const float In_Stamina);
};
