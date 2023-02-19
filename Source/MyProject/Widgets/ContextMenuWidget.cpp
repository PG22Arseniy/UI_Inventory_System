// Fill out your copyright notice in the Description page of Project Settings.


#include "ContextMenuWidget.h"
#include "Components/Button.h"
#include "InventorySlot.h" 
#include "MyProject/UI_HUD.h"


void UContextMenuWidget::NativeConstruct()
{

	Super::NativeConstruct();

	CancelBtn->OnClicked.AddDynamic(this, &UContextMenuWidget::Cancel);
	DropBtn->OnClicked.AddDynamic(this, &UContextMenuWidget::Drop);
	InspectBtn->OnClicked.AddDynamic(this, &UContextMenuWidget::Inspect);
}

void UContextMenuWidget::Cancel()
{

	// Hide context menu and stop highlighting slot

	SetVisibility(ESlateVisibility::Hidden);

	if (!ChosenSlot) return; 
	 
	ChosenSlot->StopHighLight();
	
}

void UContextMenuWidget::Drop()
{
	if (!ChosenSlot) return;

	ChosenSlot->EmptySlot(ChosenSlot); 
	Cancel();
}

void UContextMenuWidget::Inspect()
{
	// Toast message with item info
	ChosenSlot->MyHUD->DisplayToastMessage(ChosenSlot->OccupyingItem->ItemName, ChosenSlot->OccupyingItem->ItemDescription); 
	Cancel();
}
