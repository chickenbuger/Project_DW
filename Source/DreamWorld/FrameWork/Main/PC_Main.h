// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Main.generated.h"

/**
 * 
 */
class UNiagaraSystem;

class UInputMappingContext;
class UInputAction;

UCLASS()
class DREAMWORLD_API APC_Main : public APlayerController
{
	GENERATED_BODY()
	
public:
	/** »ý¼ºÀÚ */
	APC_Main();

public:
	/** Getter */
	TObjectPtr<UNiagaraSystem> GetCursorEffect() const { return m_VFX_Cursor; }

	/** Setter */
	void SetCursorEffect(TObjectPtr<UNiagaraSystem> _VFX_Cursor) { m_VFX_Cursor = _VFX_Cursor; }

protected:
	virtual void BeginPlay();
	virtual void SetupInputComponent() override;

	/** Input Handler for Move Action */
	void OnInputStarted(); //Input Start
	void OnDestinationTriggered(); // Every Tick Checked when input is Held down
	void OnDestinationReleased(); 

private:
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	float m_ShortPressThreshold;	

	/** Player Click Input VFX */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | VFX", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UNiagaraSystem> m_VFX_Cursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> m_DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UInputAction> m_MoveClickAction;

	FVector m_CachedDestination; //Player Location
	float m_FollowTime; //How long did you press it
};