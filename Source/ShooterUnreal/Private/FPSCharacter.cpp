// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mWeaponPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponPoint"));
	mWeaponPoint->bCastDynamicShadow = false;
	mWeaponPoint->CastShadow = false;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mCamera->SetupAttachment(GetCapsuleComponent());
	mCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::MoveCallBack(const FInputActionValue& aValue)
{
	if (IsValid(Controller))
	{
		const FVector2D MoveValue {aValue.Get<FVector2D>()};
		const FRotator MoveRotator {FRotator(0, Controller->GetControlRotation().Yaw, 0)};

		if (MoveValue.Y != 0.0f)
		{
			const FVector Dir {MoveRotator.RotateVector(FVector::ForwardVector)};
			AddMovementInput(Dir, MoveValue.Y);
		}
		if (MoveValue.X != 0.0f)
		{
			const FVector Dir {MoveRotator.RotateVector(FVector::RightVector)};
			AddMovementInput(Dir, MoveValue.X);
		}
	}
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* EInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	EInputSubsystem->ClearAllMappings();
	EInputSubsystem->AddMappingContext(mInputMapping, 0);

	UEnhancedInputComponent* EInputComponent {Cast<UEnhancedInputComponent>(PlayerInputComponent)};
	EInputComponent->BindAction(mInputData->InputMove, ETriggerEvent::Triggered, this, &AFPSCharacter::MoveCallBack);
}