
#pragma once

#include "CoreMinimal.h"
#include "../../ENUM/PlayerEnum.h"
#include "Components/ActorComponent.h"
#include "AC_AttackManager.generated.h"

#ifndef DEBUGMODE
#define DEBUGMODE 1
#endif

#ifndef LOGMODE
#define LOGMODE 1
#endif

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
	void CallAttemptBoxAttack(TObjectPtr<AActor> in_Player, const FVector in_AttackArea,  float in_Damage);

	void CallAttemptAttack(const int In_SkillID);

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
	/* Attack Check */
	//Box
	bool CheckBoxTypeAttack(const FVector In_BoxHalfSize, TArray<FHitResult>& OutHits);

	//Circle
	bool CheckCircleTypeAttack(const float In_Radius, TArray<FHitResult>& OutHits);

	//Arc
	bool CheckArcTypeAttack(const FVector In_BoxHalfSize, const uint32 In_Range, TArray<FHitResult>& OutHits);

	bool CheckTheScopeOfTheBoxAttack(const FVector In_BoxHalfSize, const uint32 In_Range, TArray<FHitResult>& OutHits);
};
