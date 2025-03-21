﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Enemy/NC_EnemyBase.h"
#include "DreamWorld/Enemy/EnemyDamageWidget.h"
#include "DreamWorld/Widget/Enemy/W_EnemyHPBar.h"
#include "DreamWorld/FrameWork/Main/GI_Main.h"

#include "Components/WidgetComponent.h"

// Sets default values
ANC_EnemyBase::ANC_EnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpWidget"));
	if (nullptr == m_HpBar)
	{
		return;
	}
	m_HpBar->SetupAttachment(GetMesh());
	m_HpBar->SetRelativeLocation(FVector{ 0.f,0.f,180.f });

	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef = TEXT("WidgetBlueprint'/Game/Widget/Enemy/UW_EnemyHpBar.UW_EnemyHpBar_C'");
	if (HpBarWidgetRef.Class)
	{
		m_HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		m_HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		m_HpBar->SetDrawSize(FVector2D{ 100.f,10.0f });
		m_HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	m_MaxHp		= 100.0f;
	m_Hp			= 100.0f;
}

void ANC_EnemyBase::RecieveDamage(float In_Damage)
{
	//Pawn 데이터 확인(싱글 게임이라 첫 번째 플레이어 컨트롤러가 플레이어
	if (nullptr == GetWorld()) { return; }
	if (nullptr == GetWorld()->GetFirstPlayerController()) { return; }
	if (nullptr == GetWorld()->GetFirstPlayerController()->AcknowledgedPawn) { return; }

	//GameInstance 가져오기
	if (nullptr == GetGameInstance()) return;
	TObjectPtr<UGI_Main> gameInstance = Cast<UGI_Main>(GetGameInstance());
	//Damage Indicator 받아오기(Pooling)
	TObjectPtr<AEnemyDamageWidget> damageIndicator = gameInstance->RequestDamageIndicator();

	//플레이어와 head소켓 위치 준비
	TObjectPtr<APawn> pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	const FVector headLoc = GetMesh()->GetSocketLocation(FName("head"));

	//위치 조정
	FVector SpawnLoaction;
	SpawnLoaction = headLoc + pawn->GetActorUpVector() * 20.f + pawn->GetActorRightVector() * 20.f;

	damageIndicator->RequestStart(SpawnLoaction, In_Damage);

	//Damage
	m_Hp -= In_Damage;
	DeleMuti_Func_HpChanged.Broadcast();
}

// Called when the game starts or when spawned
void ANC_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	DeleMuti_Func_HpChanged.AddUFunction(this, FName("CallDeleMuti_Func_HpChanged"));

	Init(100.0f);
}

void ANC_EnemyBase::Init(float in_MaxHp)
{
	m_MaxHp = in_MaxHp;
	m_Hp = in_MaxHp;

	DeleMuti_Func_HpChanged.Broadcast();
}

void ANC_EnemyBase::CallDeleMuti_Func_HpChanged()
{
	TObjectPtr<UW_EnemyHPBar> hpbar = Cast<UW_EnemyHPBar>(m_HpBar->GetUserWidgetObject());
	if (nullptr == hpbar)
	{
		return;
	}

	hpbar->UpdateHPBar(m_Hp, m_MaxHp);
}

// Called to bind functionality to input
void ANC_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called every frame
void ANC_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
