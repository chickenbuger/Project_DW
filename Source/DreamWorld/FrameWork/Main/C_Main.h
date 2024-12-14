// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Appearance/C_Appearance.h"
#include "GameFramework/Character.h"
#include "C_Main.generated.h"

class UAC_AttackManager;

UCLASS()
class DREAMWORLD_API AC_Main : public AC_Appearance
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Main();

public:
	//Offense
	void RequestedAttack(const int32 in_SkillID);

	//Take Damage
	void ReceiveDamage(float In_Damage);

	//Animation
	void RequestAnimationMontage(TObjectPtr<UAnimMontage> in_AnimMontage, float In_AttackSpeed=1.f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAC_AttackManager> m_AttackManager;

private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* in_Montage, bool bInterrupted);
};
