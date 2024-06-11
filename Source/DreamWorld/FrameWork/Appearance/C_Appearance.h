// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Appearance.generated.h"

UCLASS()
class DREAMWORLD_API AC_Appearance : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Appearance();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_HeadDress;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_Hair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_Face;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_Shoulder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_Cloth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_Glove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_Belt;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_SM_Shoes;
};