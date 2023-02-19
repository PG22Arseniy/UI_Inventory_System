// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDropItem.generated.h"


class AInventoryItem;
class UInventorySlot;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UDragDropItem : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInventoryItem* PickedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventorySlot* PreviousSlot;

	
};
