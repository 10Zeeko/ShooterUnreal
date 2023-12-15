// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputConfigData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Utils.h"
#include "FPSCharacter.generated.h"

class UInputMappingContext;
class UInputConfigData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClick);

UCLASS()
class SHOOTERUNREAL_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mWeaponPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* mInputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputConfigData* mInputData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int mMoveSpeed {2U};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mCurrentHealth {100.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mMaxHealth {100.f};

	UPROPERTY(BlueprintAssignable)
	FOnClick evOnClick;

protected:
	virtual void BeginPlay() override;

private:
	
	void MoveCallBack(const FInputActionValue& aValue);
	
	void LookCallBack(const FInputActionValue& aValue);

	void OnClickCallBack(const FInputActionValue& aValue);
	UPROPERTY(EditAnywhere)
	UCameraComponent* mCamera;
};
