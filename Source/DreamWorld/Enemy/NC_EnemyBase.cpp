// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Enemy/NC_EnemyBase.h"

// Sets default values
ANC_EnemyBase::ANC_EnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANC_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
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
