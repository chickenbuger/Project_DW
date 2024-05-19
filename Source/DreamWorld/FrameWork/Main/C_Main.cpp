// Fill out your copyright notice in the Description page of Project Settings.

#include "DreamWorld/Framework/Main/C_Main.h"

// Sets default values
AC_Main::AC_Main()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Main::BeginPlay()
{
	Super::BeginPlay();
	
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

