// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	UCharacterMovementComponent* characterMovement {GetCharacterMovement()};
	characterMovement->BrakingFriction = 10.0f;
	characterMovement->MaxAcceleration = 10000.0f;
	characterMovement->MaxWalkSpeed = 1000.0f;
	characterMovement->JumpZVelocity = 600.0f;
	characterMovement->AirControl = 1.0f;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	mWeaponPoint->AttachToComponent(GetMesh(), {EAttachmentRule::SnapToTarget, true}, FName(TEXT("WeaponPointSocket")));
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	EInputComponent->BindAction(mInputData->InputLook, ETriggerEvent::Triggered, this, &AFPSCharacter::LookCallBack);
	EInputComponent->BindAction(mInputData->InputJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EInputComponent->BindAction(mInputData->InputMouseClick, ETriggerEvent::Started, this, &AFPSCharacter::OnClickCallBack);
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

void AFPSCharacter::LookCallBack(const FInputActionValue& aValue)
{
	if (IsValid(Controller))
	{
		const FVector2d LookValue {aValue.Get<FVector2d>()};

		if (LookValue.X != 0)
		{
			AddControllerYawInput(LookValue.X);
		}
		if (LookValue.Y != 0)
		{
			AddControllerPitchInput(LookValue.Y);
		}
	}
}

void AFPSCharacter::OnClickCallBack(const FInputActionValue& aValue)
{
	if (IsValid(Controller))
	{
		mMoveSpeed += 10;
		evOnClick.Broadcast();
	}
}