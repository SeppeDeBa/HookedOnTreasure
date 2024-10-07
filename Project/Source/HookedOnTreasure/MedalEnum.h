// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MedalEnum.generated.h"
/**
 * 
 */


UENUM(BlueprintType)
enum class EMedalType : uint8
{
	BLANK UMETA(DisplayName = "BLANK"),
	BRONZE UMETA(DisplayName = "BRONZE"),
	SILVER UMETA(DisplayName = "SILVER"),
	GOLD UMETA(DisplayName = "GOLD"),
	

};