// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EnemyDamageText.generated.h"

/**
 * 
 */
class UTextBlock;
class AEnemyDamageWidget;

UCLASS()
class DREAMWORLD_API UW_EnemyDamageText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	void SetDamage(const float In_Damage);
	void SetOwnerActor(AEnemyDamageWidget& In_OwnerActor);

public:
	TObjectPtr<AEnemyDamageWidget> GetOwnerActor();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void RequestAnimationPlay();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock> m_Text_Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyDamageWidget> m_OwnerActor;
};
