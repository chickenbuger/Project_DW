// Fill out your copyright notice in the Description page of Project Settings.

#include "DreamWorld/Framework/Main/C_Main.h"
#include "DreamWorld/FrameWork/Main/PS_Main.h"

/** Components */
#include "Components/CapsuleComponent.h"
#include "DreamWorld/FrameWork/ActorComponent/AC_AttackManager.h"
#include "DreamWorld/FrameWork/ActorComponent/AC_SkillManager.h"

// Sets default values
AC_Main::AC_Main()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_AttackManager = CreateDefaultSubobject<UAC_AttackManager>(TEXT("AttackManager"));
	if (nullptr == m_AttackManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("AC_Main :: m_AttackManager is NULL"));
		return;
	}

	m_SkillManager = CreateDefaultSubobject<UAC_SkillManager>(TEXT("SkillManager"));
	if (nullptr == m_SkillManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState_Main :: SkillManger is NULL"));
		return;
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
}

void AC_Main::RequestedAttack(const int32 in_SkillID)
{
	TObjectPtr<APS_Main> playerstate = GetPlayerState<APS_Main>();
	if (nullptr == playerstate) { return; }
	//Skill ID�� �ùٸ��� Ȯ�� Default : -1
	if (0 > in_SkillID) { return; }
	if (nullptr == m_AttackManager) { return; }


	m_AttackManager->CallAttemptAttack(in_SkillID);
	playerstate->RequestBasicAttackAnimation();
}

void AC_Main::ReceiveDamage(float In_Damage)
{
	TObjectPtr<APS_Main> playerstate = GetPlayerState<APS_Main>();
	if (nullptr == playerstate) { return; }

	playerstate->ReceiveDamage(In_Damage);
}

void AC_Main::RequestAnimationMontage(TObjectPtr<UAnimMontage> in_AnimMontage, float In_AttackSpeed)
{
	if (nullptr == in_AnimMontage)
	{
		return;
	}

	if (!(GetMesh() && GetMesh()->GetAnimInstance()))
	{
		return;
	}

	// �ִϸ��̼� ���� �������̼�
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject<AC_Main>(this, &AC_Main::OnMontageEnded);

	// Mesh�� Part�� ���ҵǾ��ֱ⿡ ��� �ִϸ��̼��� �����������
	TArray<TObjectPtr<USceneComponent>> children;
	GetMesh()->GetChildrenComponents(true, children);

	//for-each ��� Part ��ȯ
	for (TObjectPtr<USceneComponent> child : children)
	{
		// SkeletalMesh Component Ȯ��
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

			childMesh->GetAnimInstance()->Montage_Play(in_AnimMontage, In_AttackSpeed);
		}
	}

	GetMesh()->GetAnimInstance()->Montage_Play(in_AnimMontage, In_AttackSpeed);
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate, in_AnimMontage);
}

TObjectPtr<UAC_AttackManager> AC_Main::GetAttackManager() const
{
	if (nullptr == m_AttackManager)
	{
		return nullptr;
	}

	return m_AttackManager;
}

TObjectPtr<UAC_SkillManager> AC_Main::GetSkillManager() const
{
	if (nullptr == m_SkillManager)
	{
		return nullptr;
	}

	return m_SkillManager;
}

// Called when the game starts or when spawned
void AC_Main::BeginPlay()
{
	Super::BeginPlay();

	//NewObject ���Ŀ� ������ �ʿ�, ������ ������Ʈ�� Ȱ��ȭ �ϴµ� �ʼ�
	m_AttackManager->RegisterComponent();
	m_AttackManager->SetOwnerCharacter(*this);
	m_SkillManager->RegisterComponent();
	m_SkillManager->SetOwnerCharacter(*this);
}

void AC_Main::OnMontageEnded(UAnimMontage* in_Montage, bool bInterrupted)
{
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

