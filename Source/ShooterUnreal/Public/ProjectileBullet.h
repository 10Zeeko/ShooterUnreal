// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBullet.generated.h"

UCLASS()
class SHOOTERUNREAL_API AProjectileBullet : public AActor
{
	GENERATED_BODY()
	
public:
	AProjectileBullet();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* apSphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* apProjectileMovementComponent;
	
protected:
	virtual void BeginPlay() override;
	
};
