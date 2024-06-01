// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Main.generated.h"

UCLASS()
class DREAMWORLD_API AC_Main : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Main();

public:
	//Offense
	void UseSkill(int32 in_SkillID);
	void BasicAttack();

	//Animation
	void RequestAnimationMontage(TObjectPtr<UAnimMontage> in_AnimMontage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
