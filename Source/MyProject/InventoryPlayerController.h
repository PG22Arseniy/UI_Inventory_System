// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryPlayerController.generated.h"

class UUSerWidget;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AInventoryPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void AddWidgetToViewPort(UUserWidget* Widget, int32 ZOrder);
};
