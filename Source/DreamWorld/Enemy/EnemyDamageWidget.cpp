// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Enemy/EnemyDamageWidget.h"
#include "DreamWorld/Widget/Enemy/W_EnemyDamageText.h"

#include "Components/WidgetComponent.h"

// Sets default values
AEnemyDamageWidget::AEnemyDamageWidget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_DamageWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	if (nullptr == m_DamageWidget)
	{
		return;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> DamageWidgetRef = TEXT("WidgetBlueprint'/Game/Widget/Enemy/UW_EnemyDamageText.UW_EnemyDamageText_C'");
	if (DamageWidgetRef.Class)
	{
		m_DamageWidget->SetWidgetClass(DamageWidgetRef.Class);
		m_DamageWidget->SetWidgetSpace(EWidgetSpace::Screen);
		m_DamageWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void AEnemyDamageWidget::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyDamageWidget::InitDamage() const
{
	TObjectPtr<UW_EnemyDamageText> damagetext = Cast<UW_EnemyDamageText>(m_DamageWidget->GetUserWidgetObject());
	if (nullptr == damagetext)
	{
		return;
	}

	damagetext->SetDamage(m_Damage);
}

// Called every frame
void AEnemyDamageWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

