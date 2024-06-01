// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

/** Enum */
#include "../../ENUM/PlayerEnum.h"

#include "AC_PlayerAnimation.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DREAMWORLD_API UAC_PlayerAnimation : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_PlayerAnimation();

public:
	void Init();

	//Basic Attack
	void RequestBasicAttack(EPlayerWeaponState in_WeaponState);

public:
	/** Getter */
	TObjectPtr<APawn> GetOwnerCharacter() const { return m_OwnerCharacter; }

	/** Setter */
	void SetOwnerCharacter(TObjectPtr<APawn> in_OwnerChacter) { m_OwnerCharacter = in_OwnerChacter; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TMap<EPlayerWeaponState, TObjectPtr<UAnimMontage>> m_BasicAttackAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APawn> m_OwnerCharacter;

private:
	void InitBasicAttackAnimation();
};

/*
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
*/