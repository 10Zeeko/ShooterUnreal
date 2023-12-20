// Fill out your copyright notice in the Description page of Project Settings.


#include "BPC_WeaponProjectile.h"
#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BillboardComponent.h"

UBPC_WeaponProjectile::UBPC_WeaponProjectile()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBPC_WeaponProjectile::OnFireCallback()
{
	//Super::OnFireCallback();
	if (!mpOwnerCharacter) return;
	const UWorld* pWorld {GetWorld()};
	if (pWorld == nullptr) return;

	const UCameraComponent* PlayerCamera {mpOwnerCharacter->GetCamera()};

	//If the usefulactorbp is valid
	if(aProjectileBulletBP)
	{
		const FRotator CameraRotation {PlayerCamera->GetComponentRotation()};
		const FVector StartPosition {GetOwner()->GetActorLocation() + CameraRotation.RotateVector(mpMuzzleOffset->GetComponentLocation())};
		//Spawn parameters for the current spawn.
		//We can use this for a number of options like disable collision or adjust the spawn position
		//if a collision is happening in the spawn point etc..
		FActorSpawnParameters SpawnParams;
 
		//Actual Spawn. The following function returns a reference to the spawned actor
		AProjectileBullet* ActorRef = GetWorld()->SpawnActor<AProjectileBullet>(aProjectileBulletBP, FTransform(StartPosition), SpawnParams);
 
		GLog->Log("Spawned the UsefulActor.");
	}
}
