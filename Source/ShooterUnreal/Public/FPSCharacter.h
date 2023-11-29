// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfigData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UInputMappingContext;
class UInputConfigData;

UCLASS()
class SHOOTERUNREAL_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mWeaponPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInputMappingContext* mInputMapping;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInputConfigData* mInputData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int mMoveSpeed {2U};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mCurrentHealth {100.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mMaxHealth {100.f};

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;
};
