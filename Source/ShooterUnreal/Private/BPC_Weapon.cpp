#include "BPC_Weapon.h"

#include "FPSCharacter.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBPC_Weapon::UBPC_Weapon()
{
	PrimaryComponentTick.bCanEverTick = true;
	mpMuzzleOffset = CreateDefaultSubobject<UBillboardComponent>(TEXT("ShootPoint"));
}

void UBPC_Weapon::AttachWeapon(AFPSCharacter* apPlayerCharacter)
{
	mpOwnerCharacter = apPlayerCharacter;
	if (mpOwnerCharacter != nullptr && mpOwnerCharacter->mpWeaponEquipped == nullptr)
	{
		mpOwnerCharacter->mpWeaponEquipped = this;
		FAttachmentTransformRules AttachRules {EAttachmentRule::SnapToTarget, true};
		GetOwner()->AttachToComponent(mpOwnerCharacter->GetWeapon(), AttachRules, FName(TEXT("Weapon")));

		mpOwnerCharacter->evOnClick.AddDynamic(this, &UBPC_Weapon::OnFireCallback);
	}
}

void UBPC_Weapon::OnFireCallback()
{
	if (!mpOwnerCharacter) return;
	const UWorld* pWorld {GetWorld()};
	if (pWorld == nullptr) return;

	const UCameraComponent* PlayerCamera {mpOwnerCharacter->GetCamera()};

	const FRotator CameraRotation {PlayerCamera->GetComponentRotation()};
	const FVector StartLocation {GetOwner()->GetActorLocation() + CameraRotation.RotateVector(mpMuzzleOffset->GetComponentLocation())};
	const FVector EndLocation {StartLocation + UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation()) * mShootRange};

	FCollisionQueryParams QueryParams {};
	QueryParams.AddIgnoredActor(mpOwnerCharacter);
	FHitResult HitResult {};
	pWorld->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Camera, QueryParams);
	DrawDebugLine(pWorld, StartLocation, EndLocation, HitResult.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	if (HitResult.bBlockingHit && IsValid(HitResult.GetActor()))
	{
		ScreenD(Format1("%s", *HitResult.GetActor()->GetName()));
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), mDamage, mpOwnerCharacter->GetController(), GetOwner(), {});
	}
}

void UBPC_Weapon::BeginPlay()
{
	Super::BeginPlay();
}

void UBPC_Weapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

