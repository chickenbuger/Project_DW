// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/ActorComponent/AC_PlayerAnimation.h"

/** Player */
#include "DreamWorld/FrameWork/Main/C_Main.h"

/** Construct Helper */
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UAC_PlayerAnimation::UAC_PlayerAnimation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	Init();

	m_UseAnimation = false;
}

void UAC_PlayerAnimation::Init()
{
	//Basic Attack Animation
	InitBasicAttackAnimation();
	
	//Skill Animation
	InitSkillAnimation();
}

void UAC_PlayerAnimation::RequestBasicAttack(EPlayerWeaponState In_WeaponState)
{
	if (false == AnimationCanUsing())
	{
		return;
	}

	if (nullptr == m_BasicAttackAnimation.Find(In_WeaponState))
	{
		return;
	}
	
	TObjectPtr<APawn> ownerPawn = GetOwnerCharacter();
	if (nullptr == ownerPawn)
	{
		return;
	}

	TObjectPtr<AC_Main> ownerCharacter = Cast<AC_Main>(ownerPawn);
	if (nullptr == ownerCharacter)
	{
		return;
	}

	UAC_PlayerAnimation::AnimationStart();
	ownerCharacter->RequestAnimationMontage(m_BasicAttackAnimation[In_WeaponState]);
}

void UAC_PlayerAnimation::RequestSkill(EPlayerWeaponState In_WeaponState, int32 In_SkillID)
{
	if (false == AnimationCanUsing())
	{
		return;
	}

	if (nullptr == m_SkillAnimation[In_SkillID - 1])
	{
		return;
	}

	TObjectPtr<APawn> ownerPawn = GetOwnerCharacter();
	if (nullptr == ownerPawn)
	{
		return;
	}

	TObjectPtr<AC_Main> ownerCharacter = Cast<AC_Main>(ownerPawn);
	if (nullptr == ownerCharacter)
	{
		return;
	}

	UAC_PlayerAnimation::AnimationStart();
	ownerCharacter->RequestAnimationMontage(m_SkillAnimation[In_SkillID - 1]);
}

/** 
* Can Use -> True
* Can't Use -> False
*/
bool UAC_PlayerAnimation::AnimationCanUsing()
{
	return !m_UseAnimation;
}

void UAC_PlayerAnimation::AnimationStart()
{
	m_UseAnimation = true;
}

void UAC_PlayerAnimation::AnimationFinish()
{
	m_UseAnimation = false;
}

// Called when the game starts
void UAC_PlayerAnimation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAC_PlayerAnimation::InitBasicAttackAnimation()
{
	//none is null
	m_BasicAttackAnimation.Add(EPlayerWeaponState::None, nullptr);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> NoWeaponBaiscAttackObject(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Player/Anim/Montage/AS_PlayerLeftJab_Montage.AS_PlayerLeftJab_Montage'"));
	if (NoWeaponBaiscAttackObject.Succeeded())
	{
		m_BasicAttackAnimation.Add(EPlayerWeaponState::NoWeapon, NoWeaponBaiscAttackObject.Object);
	}
}

void UAC_PlayerAnimation::InitSkillAnimation()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SkillID_1(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Player/Anim/Montage/AS_PlayerKick1_Montage.AS_PlayerKick1_Montage'"));
	if(SkillID_1.Succeeded())
	{
		m_SkillAnimation.Add(SkillID_1.Object);
	}
}

/*
* Tick
// Called every frame
void UAC_PlayerAnimation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

