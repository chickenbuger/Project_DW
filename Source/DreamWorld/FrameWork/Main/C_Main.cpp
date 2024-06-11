// Fill out your copyright notice in the Description page of Project Settings.

#include "DreamWorld/Framework/Main/C_Main.h"
#include "DreamWorld/FrameWork/Main/PS_Main.h"

/** Components */
#include "Components/CapsuleComponent.h"
#include "DreamWorld/FrameWork/ActorComponent/AC_AttackManager.h"

// Sets default values
AC_Main::AC_Main()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_AttackManager = CreateDefaultSubobject<UAC_AttackManager>(TEXT("AttackManager"));
	if (nullptr == m_AttackManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("AC_Main :: m_AttackManager is NULL"));
		return;
	}

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

	if (nullptr == m_AttackManager)
	{
		return;
	}

	m_AttackManager->CallAttemptAttack(this, 10.f);
	playerstate->RequestBasicAttackAnimation();
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

	// 애니메이션 종료 델리게이션
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject<AC_Main>(this, &AC_Main::OnMontageEnded);

	// Mesh가 Part로 분할되어있기에 모두 애니메이션을 설정해줘야함
	TArray<TObjectPtr<USceneComponent>> children;
	GetMesh()->GetChildrenComponents(true, children);

	//for-each 모든 Part 순환
	for (TObjectPtr<USceneComponent> child : children)
	{
		// SkeletalMesh Component 확인
		if (TObjectPtr<USkeletalMeshComponent> childMesh = Cast<USkeletalMeshComponent>(child))
		{
			if (nullptr == childMesh)
			{
				return;
			}
			if (nullptr == childMesh->GetAnimInstance())
			{
				continue;
			}

			childMesh->GetAnimInstance()->Montage_Play(in_AnimMontage);
		}
	}
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate, in_AnimMontage);
	GetMesh()->GetAnimInstance()->Montage_Play(in_AnimMontage);
}

// Called when the game starts or when spawned
void AC_Main::BeginPlay()
{
	Super::BeginPlay();
	
	m_AttackManager->SetOwnerCharacter(this);
}

void AC_Main::OnMontageEnded(UAnimMontage* in_Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnMontageEnded"));

	if (bInterrupted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Montage interrupted on Mesh"));
		return;
	}

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

