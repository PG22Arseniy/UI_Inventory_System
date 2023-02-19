// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolTipWidget.generated.h"


class UTextBlock;
/**
 * 
 */

UCLASS()
class MYPROJECT_API UToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* ItemDescription; 

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* ItemMass; 
};
