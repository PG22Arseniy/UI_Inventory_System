// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToastMessage.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UToastMessage : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ToastMessage;


	UPROPERTY(EditAnywhere, meta = (BindWidget)) 
	UTextBlock* ToastHeader; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 10))
	float ToastLifeTime = 4.0f;
};
