// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Main/PC_Main.h"
/** character */
#include "DreamWorld/FrameWork/Main/PS_Main.h"
#include "DreamWorld/FrameWork/Main/C_Main.h"

/** Input */
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

/** AI Library */
#include "Blueprint/AIBlueprintHelperLibrary.h"

/** VFX */
#include "NiagaraFunctionLibrary.h"

APC_Main::APC_Main()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	m_CachedDestination = FVector::ZeroVector;
	m_FollowTime = 0.0f;
}

void APC_Main::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(m_DefaultMappingContext, 0);
	}
}

void APC_Main::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		// Move
		EnhancedInputComponent->BindAction(m_MoveClickAction, ETriggerEvent::Started, this, &APC_Main::OnInputStarted);	
		EnhancedInputComponent->BindAction(m_MoveClickAction, ETriggerEvent::Triggered, this, &APC_Main::OnDestinationTriggered);
		EnhancedInputComponent->BindAction(m_MoveClickAction, ETriggerEvent::Completed, this, &APC_Main::OnDestinationReleased);
		EnhancedInputComponent->BindAction(m_MoveClickAction, ETriggerEvent::Canceled, this, &APC_Main::OnDestinationReleased);

		//Attack
		EnhancedInputComponent->BindAction(m_BasicAttackAction, ETriggerEvent::Started, this, &APC_Main::OnBasicAttackStarted);
		EnhancedInputComponent->BindAction(m_BasicAttackAction, ETriggerEvent::Triggered, this, &APC_Main::OnBasicAttackTriggered);
		EnhancedInputComponent->BindAction(m_BasicAttackAction, ETriggerEvent::Completed, this, &APC_Main::OnBasicAttackReleased);
		EnhancedInputComponent->BindAction(m_BasicAttackAction, ETriggerEvent::Canceled, this, &APC_Main::OnBasicAttackReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APC_Main::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TObjectPtr<APS_Main> MainPlayerState = Cast<APS_Main>(PlayerState);
	if (nullptr == MainPlayerState)
	{
		return;
	}

	MainPlayerState->Init();
}

void APC_Main::OnUnPossess()
{
	Super::OnUnPossess();

}

void APC_Main::OnInputStarted()
{
	StopMovement();
}

void APC_Main::OnDestinationTriggered()
{
	TObjectPtr<APS_Main> MainPlayerState = Cast<APS_Main>(PlayerState);
	if (nullptr == MainPlayerState)
	{
		return;
	}

	if (!MainPlayerState->PlayerMoveable())
	{
		return;
	}

	FHitResult Hit;
	bool bHitSuccessful = false;

	//Hit Result 
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (false == bHitSuccessful)
	{
		return;
	}

	m_CachedDestination = Hit.Location;

	TObjectPtr<APawn> ControlledPawn = GetPawn();
	if (nullptr == ControlledPawn)
	{
		return;
	}

	FVector WorldDirection = (m_CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
}

void APC_Main::OnDestinationReleased()
{
	TObjectPtr<APS_Main> MainPlayerState = Cast<APS_Main>(PlayerState);
	if (nullptr == MainPlayerState)
	{
		return;
	}

	if (!MainPlayerState->PlayerMoveable())
	{
		return;
	}

	// If it was a short press
	if (m_FollowTime <= m_ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, m_CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, m_VFX_Cursor, m_CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	m_FollowTime = 0.f;
}

void APC_Main::OnBasicAttackStarted()
{
	TObjectPtr<APS_Main> MainPlayerState = Cast<APS_Main>(PlayerState);
	if (nullptr == MainPlayerState)
	{
		return;
	}

	if (!MainPlayerState->PlayerMoveable())
	{
		return;
	}

	StopMovement();

	TObjectPtr<APawn> ControlledPawn = GetPawn();
	if (nullptr == ControlledPawn)
	{
		return;
	}

	TObjectPtr<AC_Main> ControlledCharacter = Cast<AC_Main>(ControlledPawn);
	if (nullptr == ControlledCharacter)
	{
		return;
	}

	ControlledCharacter->BasicAttack();
	//UE_LOG(LogTemp, Warning, TEXT("APC_Main::OnBasicAttackStarted"));
}

void APC_Main::OnBasicAttackTriggered()
{
	//UE_LOG(LogTemp, Warning, TEXT("APC_Main::OnBasicAttackTriggered"));
}

void APC_Main::OnBasicAttackReleased()
{
	//UE_LOG(LogTemp, Warning, TEXT("APC_Main::OnBasicAttackReleased"));
}
