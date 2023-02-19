// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InentoryGameMode.generated.h"



enum class ITEM_TYPES;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AInentoryGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
};

 

UENUM()
enum class ITEM_TYPES
{
	FLASK = 0,
	APPLE = 1,
	SWORD = 2,
	BOOK = 3,
	HERBS = 4
};