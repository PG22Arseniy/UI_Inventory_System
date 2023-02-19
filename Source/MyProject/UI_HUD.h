// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI_HUD.generated.h"



class UToastMessage;
class UNonConsumableMenuWidget;
class UConsumableMenuWidget;
class UUSerWidget;
class UContextMenuWidget;
class UInventorySlot;

UCLASS()
class MYPROJECT_API AUI_HUD : public AHUD
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

public:

	UPROPERTY()
	TArray<UInventorySlot*> GridSlots; // All Grid Slots

	
	// Widgets To Display
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(BlueprintReadOnly) 
	UUserWidget* MainWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UNonConsumableMenuWidget> NonConsumableMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UConsumableMenuWidget> ConsumableMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly)
		UNonConsumableMenuWidget* NonConsumableMenu = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UConsumableMenuWidget* ConsumableMenu = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UToastMessage> ToastMessageClass;

	UPROPERTY()
		UToastMessage* ToastMessageWidget;
	

	// Widget Display Functions 

	UFUNCTION()
	void OpenStackMenu(UInventorySlot* Slot);

	UFUNCTION()
	void OpenNonStackMenu(UInventorySlot* Slot);

	UFUNCTION()
	void CloseContextMenu();

	UFUNCTION()
	void DisplayToastMessage(FText TextName, FText TextDescription);

	UFUNCTION()
	void StopToastMessage();

	
	// Grid Management Functions

	UFUNCTION()
	void InsertSplitItems(UInventorySlot* OriginalSlot, AInventoryItem* ItemToInasert, int32 NumberOfItems);

	UFUNCTION()
	int32 GetIndexOfItem(UInventorySlot* OriginalSlot);

	UFUNCTION()
	UInventorySlot* FindNextEmptySlot (int32 StartingPosition);



	UPROPERTY()
		UInventorySlot* PreviousSlot = nullptr;

	UFUNCTION()
		const FVector2D AdjustContextMenuPos(UInventorySlot* Slot, UContextMenuWidget* ContextMenu);
};
