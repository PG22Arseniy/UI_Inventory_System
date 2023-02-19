// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject/InentoryGameMode.h"
#include "InventoryItem.generated.h"

class UTexture2D; 

UCLASS()
class MYPROJECT_API AInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ITEM_TYPES ItemType; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Stackable; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
	float Mass = 100;
};
