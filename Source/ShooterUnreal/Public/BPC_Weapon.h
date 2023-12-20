// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BPC_Weapon.generated.h"

class AFPSCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERUNREAL_API UBPC_Weapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBPC_Weapon();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AttachWeapon(AFPSCharacter* apPlayerCharacter);

	UFUNCTION(BlueprintCallable)
	virtual void OnFireCallback();

	UPROPERTY(EditDefaultsOnly)
	UBillboardComponent* mpMuzzleOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mShootRange {5000.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mDamage {2.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AFPSCharacter* mpOwnerCharacter;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
