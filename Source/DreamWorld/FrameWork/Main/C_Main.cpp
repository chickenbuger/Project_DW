// Fill out your copyright notice in the Description page of Project Settings.

#include "DreamWorld/Framework/Main/C_Main.h"
#include "DreamWorld/FrameWork/Main/PS_Main.h"

/** Components */
#include "Components/CapsuleComponent.h"

// Sets default values
AC_Main::AC_Main()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
}

void AC_Main::UseSkill(int32 in_SkillID)
{
	TObjectPtr<APS_Main> playerstate = GetPlayerState<APS_Main>();
	if (nullptr == playerstate)
	{
		return;
	}

	if (0 > in_SkillID)
	{
		return;
	}

	playerstate->RequestPlayerSkill(in_SkillID);
}

void AC_Main::BasicAttack()
{
	TObjectPtr<APS_Main> playerstate = GetPlayerState<APS_Main>();
	if (nullptr == playerstate)
	{
		return;
	}

	playerstate->RequestBasicAttack();
}

void AC_Main::RequestAnimationMontage(TObjectPtr<UAnimMontage> in_AnimMontage)
{
	if (nullptr == in_AnimMontage)
	{
		return;
	}

	if (!(GetMesh() && GetMesh()->GetAnimInstance()))
	{
		return;
	}

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AC_Main::OnMontageEnded);

	GetMesh()->GetAnimInstance()->Montage_Play(in_AnimMontage);

	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate, in_AnimMontage);
}

// Called when the game starts or when spawned
void AC_Main::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Main::OnMontageEnded(UAnimMontage* in_Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("Call OnMontageEnded"));

	TObjectPtr<APS_Main> playerstate = GetPlayerState<APS_Main>();
	if (nullptr == playerstate)
	{
		return;
	}

	playerstate->EndAnimation();
}

// Called every frame
void AC_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_Main::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

