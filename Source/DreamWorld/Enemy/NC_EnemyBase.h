// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NC_EnemyBase.generated.h"

UCLASS()
class DREAMWORLD_API ANC_EnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANC_EnemyBase();

public:
	void TakeDamage(float In_Damage);

public:
	/** Getter */
	float GetHP() const { return m_Hp; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** (float)Hp, () */
	virtual void Init(float in_Hp = 0.0f);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_Hp;
};
