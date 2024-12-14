// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../FrameWork/ParentPlayerState/PS_CharacterStatusDetail.h"
#include "PS_Main.generated.h"

/**
 * 
 */
class UAC_SkillManager;
class UAC_PlayerAnimation;

UCLASS()
class DREAMWORLD_API APS_Main : public APS_CharacterStatusDetail
{
	GENERATED_BODY()
	
public:
	APS_Main();

public:
	//Init
	void Init();
	
	//Attack
	void RequestBasicAttackAnimation();
	void RequestPlayerSkill(int32 In_SkillID);

	//Animation
	void EndAnimation();

	//Move
	bool PlayerMovable();

public:
	//Getter
	FName				GetCharacterName() const				{ return m_PlayerName; }

	//Setter
	void				SetCharacterName(FName In_PlayerName)			{ m_PlayerName = In_PlayerName; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Name", meta = (AllowPrivateAccess = "true"))
	FName m_PlayerName;
	
	/** Actor Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAC_SkillManager> m_SkillManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAC_PlayerAnimation> m_PlayerAnimationManager;
};
