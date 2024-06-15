// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/ActorComponent/AC_SkillManager.h"

// Sets default values for this component's properties
UAC_SkillManager::UAC_SkillManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//Tick함수 사용시 True
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAC_SkillManager::Init()
{
}

// Called when the game starts
void UAC_SkillManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

/*
* Tick 함수
// Called every frame
void UAC_SkillManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

*/