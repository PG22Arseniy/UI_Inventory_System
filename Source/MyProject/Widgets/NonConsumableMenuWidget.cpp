// Fill out your copyright notice in the Description page of Project Settings.


#include "NonConsumableMenuWidget.h"
#include "Components/Button.h"
#include "InventorySlot.h" 

void UNonConsumableMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReadBtn->OnClicked.AddDynamic(this, &UNonConsumableMenuWidget::Read);
}

void UNonConsumableMenuWidget::Read()
{
	// No info what to do

	SetVisibility(ESlateVisibility::Hidden);
	Cancel(); 
}
