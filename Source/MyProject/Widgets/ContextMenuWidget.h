// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContextMenuWidget.generated.h"

class UButton; 
class UInventorySlot;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UContextMenuWidget : public UUserWidget 
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* InspectBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* DropBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* CancelBtn;

	UPROPERTY(BlueprintReadWrite)
	UInventorySlot* ChosenSlot;

	virtual void NativeConstruct() override;


	UFUNCTION()
	void Cancel();

	UFUNCTION()
	void Drop();

	UFUNCTION()
	void Inspect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = -500, ClampMax = 500))
	float OffsetX = 75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = -500, ClampMax = 500))
	float OffsetY = 75; 

};
