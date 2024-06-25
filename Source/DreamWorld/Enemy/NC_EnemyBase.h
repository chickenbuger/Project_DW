// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NC_EnemyBase.generated.h"

class UWidgetComponent;

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS()
class DREAMWORLD_API ANC_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANC_EnemyBase();

public:
	//HpChanged
	FOnHpChanged DeleMuti_Func_HpChanged;

public:
	void RecieveDamage(float In_Damage);

public:
	/** Getter */
	float GetHP()			const { return m_Hp; }
	float GetMaxHP()	const { return m_MaxHp; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** (float)MaxHp, () */
	virtual void Init(float in_MaxHp = 0.0f);

	UFUNCTION()
	virtual void CallDeleMuti_Func_HpChanged();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_Hp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_MaxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> m_HpBar;
};
