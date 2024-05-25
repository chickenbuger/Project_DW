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


protected:
	//Init
	virtual void NativeInitializeAnimation();
	//Tick
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn | Character", meta = (AllowPrivateAccess ="true"))
	TObjectPtr<APawn>		m_PlayerPawn;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly, Category = "Pawn | Speed", meta = (AllowPrivateAccess = "true"))
	FVector							m_Velocity;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly, Category = "Pawn | Speed", meta = (AllowPrivateAccess = "true"))
	float									m_Speed;
};
