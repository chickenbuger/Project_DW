// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/Widget/Test/W_TestText.h"

#include "Components/TextBlock.h"

void UW_TestText::SetTestText(FString In_TestText)
{
	if (TB_TestText)
	{
		TB_TestText->SetText(FText::FromString(In_TestText));
	}
}

void UW_TestText::NativeConstruct()
{
	Super::NativeConstruct();
}