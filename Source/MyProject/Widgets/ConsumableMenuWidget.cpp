// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableMenuWidget.h" 
#include "InventoryWidget.h" 
#include "Components/Button.h"
#include "InventorySlot.h" 
#include "Components/GridPanel.h"
#include "MyProject/UI_HUD.h"

void UConsumableMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConsumeBtn->OnClicked.AddDynamic(this, &UConsumableMenuWidget::Consume);
	SplitBtn->OnClicked.AddDynamic(this, &UConsumableMenuWidget::Split);
}

void UConsumableMenuWidget::Consume()  
{

	if (!ChosenSlot) { 

		// error , chosen slot is nullptr
		return; 
		Cancel();
	}

	// Consumed 1 item from slot
	ChosenSlot->ItemsInSlot--;

	// Empty slot if it was last item
	if (ChosenSlot->ItemsInSlot <= 0) {
		ChosenSlot->EmptySlot(ChosenSlot);
	}
	Cancel();
}

void UConsumableMenuWidget::Split()
{
	if (!ChosenSlot) 
	{ 
		// error , chosen slot is nullptr
		Cancel();
		return; 
	}

	// Don't split if there are less than 1 items
	if (ChosenSlot->ItemsInSlot <= 1) 
	{
		Cancel();
		return; 
	}

	// Split Number of items
	int32 ItemsToSplit = ChosenSlot->ItemsInSlot / 2;

	// Try Inserting split items to an empty slot
	if (ChosenSlot->MyHUD)
	ChosenSlot->MyHUD->InsertSplitItems(ChosenSlot, ChosenSlot->OccupyingItem, ItemsToSplit); 

	Cancel();
}
