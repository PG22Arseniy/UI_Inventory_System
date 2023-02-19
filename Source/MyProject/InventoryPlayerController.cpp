// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPlayerController.h"
#include "Blueprint/UserWidget.h"


void AInventoryPlayerController::AddWidgetToViewPort(UUserWidget* Widget, int32 ZOrder)
{
	Widget->AddToViewport(ZOrder); 
}
