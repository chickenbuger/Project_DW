// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

/** Enum */
#include "../../ENUM/PlayerEnum.h"

#include "PS_Main.generated.h"

/**
 * 
 */
class UAC_SkillManager;
class UAC_PlayerAnimation;

DECLARE_MULTICAST_DELEGATE(FOnChanged_Hp);
DECLARE_MULTICAST_DELEGATE(FOnChanged_Mana);
DECLARE_MULTICAST_DELEGATE(FOnChanged_Stamina);

UCLASS()
class DREAMWORLD_API APS_Main : public APlayerState
{
	GENERATED_BODY()
	
public:
	APS_Main();

public:
	FOnChanged_Hp Dele_Changed_Hp;
	FOnChanged_Mana Dele_Changed_Mana;
	FOnChanged_Stamina Dele_Changed_Stamina;

public:
	//Init
	void Init();
	void PlayerInfoWidgetInit();
	
	//Attack
	void RequestBasicAttackAnimation();
	void RequestPlayerSkill(int32 In_SkillID);

	//Take Damage
	void ReceiveDamage(float In_Damage);

	//Animation
	void EndAnimation();

	//Move
	bool PlayerMoveable();

public:
	//Getter
	FName		GetCharacterName() const				{ return m_PlayerName; }
	float			GetMaxHealth() const						{ return m_MaxHealth; }
	float			GetMaxMana() const						{ return m_MaxMana; }
	float			GetMaxStamina() const					{ return m_MaxStamina; }
	float			GetHealth() const							{ return m_Health; }
	float			GetMana() const								{ return m_Mana; }
	float			GetStamina() const							{ return m_Stamina; }

	//Setter
	void			SetCharacterName(FName In_PlayerName)		{ m_PlayerName = In_PlayerName; }
	void			SetMaxHealth(float In_MaxHelath)					{ m_MaxHealth = In_MaxHelath; }
	void			SetMaxMana(float In_MaxMana)							{ m_MaxMana = In_MaxMana; }
	void			SetMaxStamina(float In_MaxStamina)				{ m_MaxStamina = In_MaxStamina; }
	void			SetHealth(float In_Helath)									{ m_Health	= In_Helath; }
	void			SetMana(float In_Mana)										{ m_Mana	= In_Mana; }
	void			SetStamina(float In_Stamina)								{ m_Stamina = In_Stamina;  }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Name", meta = (AllowPrivateAccess = "true"))
	FName m_PlayerName;

	/** Max */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_MaxMana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_MaxStamina;

	/** Current */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float	m_Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	EPlayerWeaponState m_WeaponState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAC_SkillManager> m_SkillManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAC_PlayerAnimation> m_PlayerAnimationManager;
};
