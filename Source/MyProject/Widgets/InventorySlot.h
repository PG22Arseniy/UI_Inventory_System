// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/InventoryItem.h"
#include "InventorySlot.generated.h"

class UImage; 
class UButton;
class UTextBlock;
class AInventoryItem;
class UDragDropItem;
class UContextMenuWidget;
class AUI_HUD;
class UToolTipWidget;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

	// Widget components

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* SlotButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) 
	UImage* SlotImage;  

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HighlightBackground; 

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemCounter;


	// Occupying item data
	UPROPERTY(BlueprintReadOnly)
	bool SlotOccupied = false; 

	UPROPERTY(BlueprintReadWrite)
	AInventoryItem* OccupyingItem;

	UPROPERTY(BlueprintReadOnly)
	int32 ItemsInSlot = 0;


protected:

	// Derived Functions

	// Mouse Operations:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& Geometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InMouseEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual  void NativeOnInitialized() override;


public:

	UFUNCTION()
	FText GetItemCounter();

	UFUNCTION()
	void EmptySlot(UInventorySlot* SlotToEmpty);

	UFUNCTION()
	void PutItemInEmptySlot(UDragDropItem* DraggingItem);

	UFUNCTION()
	void SwapItems(UDragDropItem* DraggingItem);

	UFUNCTION()
	void CombineItems(UDragDropItem* DraggingItem);

	UFUNCTION()
	void ShowContextMenu();

	UFUNCTION()
	void HideContextMenu();

	UFUNCTION()
	void HighLight();

	UFUNCTION()
	void StopHighLight();


	// My HUD
	UPROPERTY(BlueprintReadOnly)
	AUI_HUD* MyHUD;


	// Tool tip
	UPROPERTY(BlueprintReadOnly)
	UToolTipWidget* ToolTip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UToolTipWidget> ToolTipClass; 



	


	
};
