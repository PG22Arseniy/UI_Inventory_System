// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h" 
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MyProject/InventoryItem.h"
#include "MyProject/InventoryPlayerController.h"
#include "MyProject/UI_HUD.h"
#include "InventoryWidget.h"  
#include "ToolTipWidget.h" 
#include "ContextMenuWidget.h"  
#include "DragDropItem.h" 
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"



FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& InMouseEvent)
{

	// Handle Context Menus

	// Detect Right Click For Context Menu
	FEventReply RightClickResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton);
	if (RightClickResult.NativeReply.IsEventHandled()) {
		ShowContextMenu();
	}


	// Handle Drag Detection

	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return ReplyResult.NativeReply;
	
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& Geometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{

	Super::NativeOnDragDetected(Geometry, InMouseEvent, OutOperation); 
 
	HideContextMenu(); 

	if (MyHUD->PreviousSlot)
		MyHUD->PreviousSlot->StopHighLight();  


	UDragDropOperation* DragOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropItem::StaticClass());

	if (OccupyingItem == nullptr) return;
	
	// Set Drag drop opertion 

	if (UDragDropItem* DraggingItem = Cast<UDragDropItem>(DragOperation)) 
	{
		SlotImage->SetOpacity(0.5); // reduce image opacity of original slot

		// Set Drag Drop Information
		DraggingItem->PreviousSlot = this;
		DraggingItem->PickedItem = OccupyingItem; 
		DraggingItem->DefaultDragVisual = DuplicateObject(this, NULL); // Set widget to the copy of this slot 

		OutOperation = DraggingItem;

	}

	
}

void UInventorySlot::NativeOnDragLeave(const FDragDropEvent& InMouseEvent, UDragDropOperation* InOperation)
{
	// On Drag Leave
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UDragDropItem* DraggedItem = Cast<UDragDropItem>(InOperation))
	{

		// Errors with Dragging item:
		if (!DraggedItem) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Drag Opertion IS NULL");
			return true;
		}

		if (!DraggedItem->PickedItem)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Drag Item IS NULL");
			return true;
		}



		//SAME SLOT CASE
		if (this == DraggedItem->PreviousSlot)
		{
			DraggedItem->PreviousSlot->SlotImage->SetOpacity(1);
			return true;  // Everything stays in place
		}


		// NEW SLOT IS EMPTY


		// We Replace Item From Previous location to the new one (current spot = this)
		if (OccupyingItem == nullptr)
		{
			PutItemInEmptySlot(DraggedItem);
			return true; 
		}


		// NEW SLOT IS NOT EMPTY


		// Same Type Stackable:
		if (DraggedItem->PickedItem->ItemType == OccupyingItem->ItemType && OccupyingItem->Stackable)
		{
			CombineItems(DraggedItem);
			return true;
		}


		// Same Type Non Stackable:
		if (DraggedItem->PickedItem->ItemType == OccupyingItem->ItemType && !OccupyingItem->Stackable)
		{
			DraggedItem->PreviousSlot->SlotImage->SetOpacity(1); 
			return true;  // Everything stays in place
		}


		// Not the same type:
		if (DraggedItem->PickedItem->ItemType != OccupyingItem->ItemType)
		{
			SwapItems(DraggedItem);
			return true;
		}

		return true;
	}

	return true;
}



void UInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemCounter->TextDelegate.BindDynamic(this, &UInventorySlot::GetItemCounter);

	// Get Refernce to HUD
	MyHUD = Cast<AUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());


	// Create Tool Tip and Store in Variable

	if (!ToolTipClass) return;

	if (!ToolTipWidget) 
	{
		ToolTip = CreateWidget<UToolTipWidget>(GetWorld()->GetFirstPlayerController(), ToolTipClass, TEXT("ToolTipWidget Widget")); 
	} 
}


FText UInventorySlot::GetItemCounter()
{
	if (ItemsInSlot > 0) return FText::AsNumber(ItemsInSlot);

	return FText(); 
}


void UInventorySlot::EmptySlot(UInventorySlot* SlotToEmpty)
{
	if (!SlotToEmpty) return;

	SlotToEmpty->SlotImage->SetOpacity(0); // No picture
	SlotToEmpty->OccupyingItem = nullptr;  // Last spot's occupying item is null
	SlotToEmpty->ItemsInSlot = 0; // No Items Are in Spot
}


void UInventorySlot::PutItemInEmptySlot(UDragDropItem* DraggedItem)
{
	// Empty Original slot and populate new one
	OccupyingItem = DraggedItem->PickedItem;
	ItemsInSlot = DraggedItem->PreviousSlot->ItemsInSlot;
	SlotImage->SetOpacity(1);

	EmptySlot(DraggedItem->PreviousSlot);
}


void UInventorySlot::SwapItems(UDragDropItem* DraggedItem)
{
	// Create A temporary Item Holder to change Items in Slots

	AInventoryItem* TempItem = OccupyingItem;
	int32 TempItemsInSlot= ItemsInSlot;


	OccupyingItem = DraggedItem->PickedItem;
	ItemsInSlot = DraggedItem->PreviousSlot->ItemsInSlot;


	DraggedItem->PreviousSlot->OccupyingItem = TempItem; // Previous slot holds new item
	DraggedItem->PreviousSlot->ItemsInSlot = TempItemsInSlot; 
	DraggedItem->PreviousSlot->SlotImage->SetOpacity(1); 
}


void UInventorySlot::CombineItems( UDragDropItem* DraggedItem)
{
	ItemsInSlot += DraggedItem->PreviousSlot->ItemsInSlot; // All items went to the new slot 

	EmptySlot(DraggedItem->PreviousSlot);
}



void UInventorySlot::ShowContextMenu()
{

	// Show Context Menu based on the type of the occu[ying item. If slot is empty then hide context menu
	if (OccupyingItem)
		if (OccupyingItem->Stackable)
			MyHUD->OpenStackMenu(this); 
		else
			MyHUD->OpenNonStackMenu(this);
	else
		MyHUD->CloseContextMenu(); 
}

void UInventorySlot::HideContextMenu()
{
	MyHUD->CloseContextMenu();
}

void UInventorySlot::HighLight()
{
	if (HighlightBackground)
	HighlightBackground->SetOpacity(1);
	 
}

void UInventorySlot::StopHighLight()
{
	if (HighlightBackground) 
	HighlightBackground->SetOpacity(0); 
}


