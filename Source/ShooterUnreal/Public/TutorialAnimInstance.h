// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TutorialAnimInstance.generated.h"

UCLASS()
class SHOOTERUNREAL_API UTutorialAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRotator mRotation;
};
