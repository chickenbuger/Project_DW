// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/FrameWork/Appearance/C_Appearance.h"

// Sets default values
AC_Appearance::AC_Appearance()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/** Create Subobject */

	m_SM_Shoes = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoes"));
	if (nullptr == m_SM_Shoes) { return; }

	m_SM_Belt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belt"));
	if (nullptr == m_SM_Belt) { return; }

	m_SM_Glove = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Glove"));
	if (nullptr == m_SM_Glove) { return; }

	m_SM_Cloth = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cloth"));
	if (nullptr == m_SM_Cloth) { return; }

	m_SM_Shoulder = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoulder"));
	if (nullptr == m_SM_Shoulder) { return; }

	m_SM_Face = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
	if (nullptr == m_SM_Face) { return; }

	m_SM_Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	if (nullptr == m_SM_Hair) { return; }

	m_SM_HeadDress	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadDress"));
	if (nullptr == m_SM_HeadDress) { return; }
	
	/** Attach */
	m_SM_Shoes->SetupAttachment(GetMesh());
	m_SM_Belt->SetupAttachment(GetMesh());
	m_SM_Glove->SetupAttachment(GetMesh());
	m_SM_Cloth->SetupAttachment(GetMesh());
	m_SM_Shoulder->SetupAttachment(GetMesh());
	m_SM_Face->SetupAttachment(GetMesh());
	m_SM_Hair->SetupAttachment(GetMesh());
	m_SM_HeadDress->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AC_Appearance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Appearance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_Appearance::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

