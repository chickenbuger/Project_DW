// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_Player.generated.h"

/**
 * 
 */
UCLASS()
class DREAMWORLD_API UAI_Player : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAI_Player() : m_PlayerPawn(nullptr), m_Velocity(FVector()), m_Speed(0.f) {}

protected:
	//Init
	virtual void NativeInitializeAnimation();
	//Tick
	virtual void NativeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn | Character", meta = (AllowPrivateAccess ="true"))
	TObjectPtr<APawn>						m_PlayerPawn;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly, Category = "Pawn | Speed", meta = (AllowPrivateAccess = "true"))
	FVector									m_Velocity;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly, Category = "Pawn | Speed", meta = (AllowPrivateAccess = "true"))
	double									m_Speed;

private:
	UFUNCTION()
	void AnimNotify_AttackTiming();
};
