// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyDamageWidget.generated.h"

class UWidgetComponent;

UCLASS()
class DREAMWORLD_API AEnemyDamageWidget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyDamageWidget();

public:
	void DetectedDamage(const float In_Damage);
	void RequestAnimationPlay();
	void RequestStart(const FVector In_loc, float In_damage);

public:
	UFUNCTION(BlueprintCallable)
	void ReturnSelf();

	UFUNCTION(BlueprintImplementableEvent)
	void RequestStartMove();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> m_DamageWidget;

	UPROPERTY()
	float m_Damage;

private:
	void InitDamage() const;
};
