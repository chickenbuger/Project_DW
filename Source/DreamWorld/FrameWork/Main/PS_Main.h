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

UCLASS()
class DREAMWORLD_API APS_Main : public APlayerState
{
	GENERATED_BODY()
	
public:
	APS_Main();

public:
	void Init();
	
	//Attack
	void RequestBasicAttack();
	void RequestPlayerSkill(int32 in_SkillID);

public:
	//Getter
	float GetHealth() const		{ return m_Health; }
	float GetMana() const			{ return m_Mana; }
	float GetStamina() const		{ return m_Stamina; }

	//Setter
	void SetHealth(float inHelath)			{ m_Health		=  inHelath; }
	void SetMana(float inMana)				{ m_Mana		=  inMana; }
	void SetStamina(float inStamina)		{ m_Stamina	=  inStamina; }

private:
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
