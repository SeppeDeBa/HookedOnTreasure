// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SavedData.generated.h"

/**
 * 
 */
UCLASS()
class HOOKEDONTREASURE_API USavedData : public USaveGame
{
	GENERATED_BODY()

public:
	USavedData();

	UPROPERTY(VisibleAnywhere)
	int level1Medal;
	UPROPERTY(VisibleAnywhere)
	int level2Medal;
	UPROPERTY(VisibleAnywhere)
	int level3Medal;
	UPROPERTY(VisibleAnywhere)
	int level4Medal;

	
};
