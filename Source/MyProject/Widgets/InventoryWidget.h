// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/InventoryItem.h"
//#include "Components/GridPanel.h" 
#include "InventoryWidget.generated.h"

class UGridPanel;
class AInventoryItem;
class UInventorySlot;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AInventoryItem>> AvailableItems;  


	UPROPERTY(EditAnywhere, meta = (BindWidget)) 
	UGridPanel* InventoryGrid;


	virtual void NativeConstruct() override; 

};
