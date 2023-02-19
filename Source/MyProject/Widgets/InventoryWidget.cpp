// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GridPanel.h" 
#include "MyProject/InventoryItem.h"
#include "MyProject/UI_HUD.h"
#include "InventorySlot.h" 
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "InventoryWidget.h"



void UInventoryWidget::NativeConstruct()
{
	
	for (auto InvSlot : InventoryGrid->GetAllChildren()) {

		if (UInventorySlot* SlotWidget = Cast<UInventorySlot>(InvSlot))  
		{
			// Populate Slots in Array of grid slots
			AUI_HUD* MyHUD = Cast<AUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			MyHUD->GridSlots.Add(SlotWidget); 


			// Randomly Populate grid with items
			if (UKismetMathLibrary::RandomBool())  
			{
				int32 RandItemNum = UKismetMathLibrary::RandomInteger(5); 

				SlotWidget->OccupyingItem = AvailableItems[RandItemNum].GetDefaultObject(); 

				SlotWidget->SlotImage->SetVisibility(ESlateVisibility::Visible);
				SlotWidget->SlotImage->SetOpacity(1);

				if (SlotWidget->OccupyingItem->Stackable)
				{
					int32 RandCounterNum = UKismetMathLibrary::RandomInteger(10)+1; 
					SlotWidget->ItemsInSlot = RandCounterNum; 
				}
			}
		} 
	}


}





