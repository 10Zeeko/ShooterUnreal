// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERUNREAL_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* InputMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* InputLook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* InputJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* InputMouseClick;
};
