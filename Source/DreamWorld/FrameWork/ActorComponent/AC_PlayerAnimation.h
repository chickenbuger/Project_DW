// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

/** Enum */
#include "../../ENUM/PlayerEnum.h"

#include "AC_PlayerAnimation.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DREAMWORLD_API UAC_PlayerAnimation : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_PlayerAnimation();

public:
	void Init();

	//Basic Attack
	void RequestBasicAttack(EPlayerWeaponState In_WeaponState, float In_AttackSpeed);

	//Skill
	void RequestSkill(EPlayerWeaponState In_WeaponState, int32 In_SkillID, float In_AttackSpeed);
	
	//Animation Using Check
	bool AnimationCanUsing() const;
	void AnimationStart();
	void AnimationFinish();

public:
	/** Getter */
	TObjectPtr<APawn>	GetOwnerCharacter() const			{ return m_OwnerCharacter; }
	bool				GetUseAnimaton() const									{ return m_UseAnimation; }

	/** Setter */
	void SetOwnerCharacter(TObjectPtr<APawn> In_OwnerChacter) { m_OwnerCharacter = In_OwnerChacter; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TMap<EPlayerWeaponState, TObjectPtr<UAnimMontage>> m_BasicAttackAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_SkillAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Check", meta = (AllowPrivateAccess = "true"))
	bool m_UseAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APawn> m_OwnerCharacter;

private:
	void InitBasicAttackAnimation();
	void InitSkillAnimation();
};

/*
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
*/