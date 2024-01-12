// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mDamage {2.0f};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AFPSCharacter* mpOwnerCharacter;
	
protected:
	UFUNCTION()
	void BeginOverlapCallback(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;
};
