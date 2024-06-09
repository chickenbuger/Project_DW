// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Enemy/NC_EnemyBase.h"

// Sets default values
ANC_EnemyBase::ANC_EnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Hp = 100.0f;
}

void ANC_EnemyBase::TakeDamage(float In_Damage)
{
	m_Hp -= In_Damage;

	UE_LOG(LogTemp, Warning, TEXT("Current Enemy HP : %f"), m_Hp);
}

// Called when the game starts or when spawned
void ANC_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANC_EnemyBase::Init(float in_Hp)
{
	m_Hp = in_Hp;
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
