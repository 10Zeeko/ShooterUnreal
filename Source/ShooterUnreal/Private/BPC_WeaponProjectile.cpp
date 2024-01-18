// Fill out your copyright notice in the Description page of Project Settings.


#include "BPC_WeaponProjectile.h"
#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/TransformCalculus3D.h"

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
		const FRotator SpawnRotation = mpOwnerCharacter->GetControlRotation();
		const FRotator CameraRotation {PlayerCamera->GetComponentRotation()};
		const FVector StartPosition {GetOwner()->GetActorLocation() + CameraRotation.RotateVector(mpMuzzleOffset->GetComponentLocation())};
		//Actual Spawn. The following function returns a reference to the spawned actor
		AProjectileBullet* ActorRef = GetWorld()->SpawnActorDeferred<AProjectileBullet>(aProjectileBulletBP, FTransform(StartPosition), mpOwnerCharacter, mpOwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		if (ActorRef)
		{
			ActorRef->SetActorRotation(SpawnRotation);
			ActorRef->mDamage = mDamage;
			ActorRef->mpOwnerCharacter = mpOwnerCharacter;
			UGameplayStatics::FinishSpawningActor(ActorRef, FTransform(StartPosition));
		}
		GLog->Log("Spawned the UsefulActor.");
	}
}

void UBPC_WeaponProjectile::AttachWeapon(AFPSCharacter* apPlayerCharacter)
{
	Super::AttachWeapon(apPlayerCharacter);
}

void UBPC_WeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	mpMuzzleOffset->SetRelativeLocation(FVector(80, 0, 0));
}
