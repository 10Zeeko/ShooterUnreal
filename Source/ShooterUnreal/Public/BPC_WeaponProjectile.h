// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPC_Weapon.h"
#include "ProjectileBullet.h"
#include "BPC_WeaponProjectile.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERUNREAL_API UBPC_WeaponProjectile : public UBPC_Weapon
{
	GENERATED_BODY()
public:
	UBPC_WeaponProjectile();
	
	virtual void OnFireCallback() override;

	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AProjectileBullet> aProjectileBulletBP;

	virtual void AttachWeapon(AFPSCharacter* apPlayerCharacter) override;

protected:
	virtual void BeginPlay() override;
};
