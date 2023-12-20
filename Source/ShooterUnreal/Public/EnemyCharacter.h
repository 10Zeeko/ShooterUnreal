// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SHOOTERUNREAL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHitCallback(AActor* apDamagedActor, float aDamage, const UDamageType* apDamageType, AController* apInstigatedBy, AActor* apDamageCauser);
	AEnemyCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* mpBoxCollision;
	
protected:
	virtual void BeginPlay() override;
};
