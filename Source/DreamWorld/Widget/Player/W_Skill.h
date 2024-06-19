// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Skill.generated.h"

/**
 * 
 */
class USizeBox;
class UBorder;

UCLASS()
class DREAMWORLD_API UW_Skill  : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void RequestUsingSkillToPlayer();

	/** Setter */
	void SetSkillID(const int32 In_SkillID) { m_Skill_ID = In_SkillID; }

	/** Getter */
	int32 GetSkillID() const { return m_Skill_ID; }

public:
	virtual void NativeConstruct() override;

private:
	/** UI */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<USizeBox>		m_SizeBox_Skill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UBorder>			m_Border_Skill;

	/** Data */

	//Default -> -1 (not Binding)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_Skill_ID;
};
