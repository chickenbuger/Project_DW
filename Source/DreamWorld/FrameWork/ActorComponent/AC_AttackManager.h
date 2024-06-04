// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_AttackManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DREAMWORLD_API UAC_AttackManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_AttackManager();

public:
	/**
	* 인자 : 공격 시도자, 데미지
	* 공격 범위 체크 및 데미지 처리
	*/
	void CallAttemptAttack(TObjectPtr<AActor> in_Player, uint32 in_Damage);

public:
	/** Getter */
	TObjectPtr<APawn> GetOwnerCharacter() const { return m_OwnerCharacter; }
	/** Setter */

	void SetOwnerCharacter(TObjectPtr<APawn> in_OwnerChacter) { m_OwnerCharacter = in_OwnerChacter; }

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APawn> m_OwnerCharacter;

private:
	bool CheckTheScopeOfTheAttack(uint32 in_Range, TArray<FHitResult>& OutHits);
};
