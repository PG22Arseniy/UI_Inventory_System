// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContextMenuWidget.h"
#include "NonConsumableMenuWidget.generated.h"


class UButton;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UNonConsumableMenuWidget : public UContextMenuWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* ReadBtn;


	virtual void NativeConstruct() override;


	UFUNCTION()
	void Read();
};
