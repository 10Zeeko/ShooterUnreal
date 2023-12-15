#include "BPC_Weapon.h"

#include "FPSCharacter.h"
#include "Utils.h"
#include "Components/BillboardComponent.h"

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
	ScreenD(TEXT("A"));
}

void UBPC_Weapon::BeginPlay()
{
	Super::BeginPlay();
}

void UBPC_Weapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

