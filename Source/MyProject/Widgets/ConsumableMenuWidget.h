// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContextMenuWidget.h"
#include "ConsumableMenuWidget.generated.h"

class UButton;
class UInventoryWidget;


UCLASS()
class MYPROJECT_API UConsumableMenuWidget : public UContextMenuWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* ConsumeBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* SplitBtn;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Consume();

	UFUNCTION()
	void Split();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CannotSplitMessage;
 
};
