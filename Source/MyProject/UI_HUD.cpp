// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HUD.h"
#include "Widgets/ConsumableMenuWidget.h"
#include "Widgets/NonConsumableMenuWidget.h"
#include "Widgets/InventorySlot.h"
#include "Widgets/ToastMessage.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void AUI_HUD::BeginPlay()
{
	UWorld* World = GetWorld();
	if (!World) return;


	// Allow mouse, click events
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
	PlayerController->bEnableMouseOverEvents = true;



	// Create and display Main Widget
	if (!MainWidgetClass) return;

	if (!MainWidget)
	{
		MainWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainWidgetClass, TEXT("Main Widget"));
		MainWidget->AddToViewport(0);
		MainWidget->SetVisibility(ESlateVisibility::Visible); 
	}


	// Create Context menus
	if (!NonConsumableMenuWidgetClass || !ConsumableMenuWidgetClass) return; 

	if (!NonConsumableMenu)
	{
		NonConsumableMenu = CreateWidget<UNonConsumableMenuWidget>(GetOwningPlayerController(), NonConsumableMenuWidgetClass, TEXT("Non Stack Menu Widget"));
		NonConsumableMenu->AddToViewport(5);
		NonConsumableMenu->SetVisibility(ESlateVisibility::Hidden);

	}

	if (!ConsumableMenu)
	{
		ConsumableMenu = CreateWidget<UConsumableMenuWidget>(GetOwningPlayerController(), ConsumableMenuWidgetClass, TEXT("Stack Menu Widget"));
		ConsumableMenu->AddToViewport(5);
		ConsumableMenu->SetVisibility(ESlateVisibility::Hidden);
	}


}

void AUI_HUD::DrawHUD()
{
	Super::DrawHUD(); 
}

void AUI_HUD::OpenStackMenu(UInventorySlot* Slot)
{
	// Close Non Stack and Open Stack menu
	NonConsumableMenu->SetVisibility(ESlateVisibility::Hidden);
	ConsumableMenu->SetVisibility(ESlateVisibility::Visible);
	ConsumableMenu->ChosenSlot = Slot;
	
	// Calculate new position on screen
	ConsumableMenu->SetPositionInViewport(AdjustContextMenuPos(Slot, ConsumableMenu)); 
}


void AUI_HUD::OpenNonStackMenu(UInventorySlot* Slot)
{
	// Close  Stack and Open Non Stack menu
	NonConsumableMenu->SetVisibility(ESlateVisibility::Visible);
	ConsumableMenu->SetVisibility(ESlateVisibility::Hidden); 
	NonConsumableMenu->ChosenSlot = Slot;

	// Calculate new position on screen
	NonConsumableMenu->SetPositionInViewport(AdjustContextMenuPos(Slot, NonConsumableMenu)); 
}

void AUI_HUD::CloseContextMenu()
{
	// close context menu
	ConsumableMenu->SetVisibility(ESlateVisibility::Hidden);
	NonConsumableMenu->SetVisibility(ESlateVisibility::Hidden); 
}

void AUI_HUD::InsertSplitItems(UInventorySlot* OriginalSlot, AInventoryItem* ItemToInsert, int32 NumberOfItems)
{
	
	// Get index of original slot
	int32 currentPos = GetIndexOfItem(OriginalSlot);

	if (currentPos < 0) // func returned -1
	{
		// Slot Not Found error
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Slot Not Found");
		return;
	}

	// Try Find Next Slot for split items 
	UInventorySlot* NextEmptySlot = FindNextEmptySlot(currentPos);


	if (!NextEmptySlot) // func returned nullptr
	{
		// No Slot Available Message
		DisplayToastMessage(FText::FromString(ANSI_TO_TCHAR("")), ConsumableMenu->CannotSplitMessage); 
		return;
	}
	
	// Provide New Slot with split items
	NextEmptySlot->OccupyingItem = ItemToInsert;
	NextEmptySlot->ItemsInSlot = NumberOfItems; 
	NextEmptySlot->SlotImage->SetOpacity(1); 

	// take away items from original slot
	OriginalSlot->ItemsInSlot -= NumberOfItems;

}

int32 AUI_HUD::GetIndexOfItem(UInventorySlot* OriginalSlot)
{
	// get index of provoded slot in grid
	for (int32 i = 0; i < GridSlots.Num(); i++)
	{
		if (GridSlots[i] == OriginalSlot) {
			return i;
		}
	}
	return -1;
}

UInventorySlot* AUI_HUD::FindNextEmptySlot(int32 StartingPosition)
{
	// Find Next Empty Slot from provided index

	for (int32 i = StartingPosition + 1; i < GridSlots.Num(); i++)
	{
		if (!GridSlots[i]->OccupyingItem) {
			return GridSlots[i];
		}
	}
	for (int32 i = StartingPosition - 1; i >= 0; i--)
	{
		if (!GridSlots[i]->OccupyingItem) {
			return GridSlots[i];
		}
	}

	// Empty slot hasn't been found
	return nullptr;
}

void AUI_HUD::DisplayToastMessage(FText TextName, FText TextDescription)
{

	if (!ToastMessageWidget) 
	{


		// Create toast widget
		ToastMessageWidget = CreateWidget<UToastMessage>(GetOwningPlayerController(), ToastMessageClass, TEXT("ToastMessage Widget"));

		// Set Toast Texts
		ToastMessageWidget->ToastHeader->Text = TextName;
		ToastMessageWidget->ToastMessage->Text = TextDescription;
		
		// Display toast widget 
		ToastMessageWidget->AddToViewport(15); 


		// Hide Widget with delay
		FTimerHandle ToastTimer;
		GetWorldTimerManager().SetTimer(ToastTimer, this, &AUI_HUD::StopToastMessage , ToastMessageWidget->ToastLifeTime, false);
	}
}

void AUI_HUD::StopToastMessage()
{
	ToastMessageWidget->RemoveFromParent();   
	ToastMessageWidget = nullptr; 
}


const FVector2D AUI_HUD::AdjustContextMenuPos(UInventorySlot* Slot, UContextMenuWidget* ContextMenu)
{

	UWorld* World = GetWorld();
	if (!World) return {0,0};


	// Stop highlighting previous slot and highlight new 
	if (PreviousSlot) PreviousSlot->StopHighLight();

	Slot->HighLight();
	PreviousSlot = Slot;


	// Get Mouse Position from player controller:
	APlayerController* PlayerController = World->GetFirstPlayerController();

	float X;
	float Y;
	PlayerController->GetMousePosition(X,Y);

	// Calculate widget postion with offsets (adjustable in BP of context menu widgets)
	const FVector2D ViewportPos = { X + ContextMenu->OffsetX , Y + ContextMenu->OffsetY }; 

	return ViewportPos; 
}