#include "EnemyCharacter.h"

#include "FPSCharacter.h"
#include  "Components/BoxComponent.h"
#include "Utils.h"
#include "ShooterUnreal/Public/Utils.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mpBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	mpBoxCollision->SetupAttachment(RootComponent);

	mAISight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));
	mAISight->SightRadius = 1250.0f;
	mAISight->LoseSightRadius = 1300.0f;
	mAISight->PeripheralVisionAngleDegrees = 90.0f;
	mAISight->DetectionByAffiliation.bDetectEnemies =
		mAISight->DetectionByAffiliation.bDetectFriendlies =
			mAISight->DetectionByAffiliation.bDetectNeutrals = true;
	mAISight->SetMaxAge(0.1f);

	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	mAIPerception->ConfigureSense(*mAISight);
	mAIPerception->SetDominantSense(mAISight->GetSenseImplementation());
	mAIPerception->OnPerceptionUpdated.AddDynamic(this, &AEnemyCharacter::OnSenseCallback);

	mCurrentVelocity = FVector::ZeroVector;
	mDistanceSQRT = BIG_NUMBER;
	
	
	OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::OnHitCallback);
}

void AEnemyCharacter::OnSenseCallback(const TArray<AActor*>& aUpdateActor)
{
	for (const auto& UpdateActor : aUpdateActor)
	{
		FActorPerceptionBlueprintInfo PerceptionInfo;
		mAIPerception->GetActorsPerception(UpdateActor, PerceptionInfo);

		if (PerceptionInfo.LastSensedStimuli[0].WasSuccessfullySensed() && Cast<AFPSCharacter>(UpdateActor))
		{			
			SetNewRotation(UpdateActor->GetActorLocation());
		}
		else
		{
			FVector AuxDir {mSpawnPosition - GetActorLocation()};
			AuxDir.Z = 0;
			if (AuxDir.SizeSquared2D() > 1.0f)
			{
				mGoBackToBase = true;
				SetNewRotation(mSpawnPosition);
			}
		}
	}
}

void AEnemyCharacter::SetNewRotation(const FVector& aTargetRot)
{
	FVector NewDir = aTargetRot - GetActorLocation();
	NewDir.Z = 0;
	mCurrentVelocity = NewDir.GetSafeNormal() * mMoveSpeed;

	mCurrentRotation = NewDir.Rotation();
	SetActorRotation(mCurrentRotation);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mCurrentVelocity.IsZero())
	{
		mNewPosition = GetActorLocation() + mCurrentVelocity * DeltaTime;

		if (mGoBackToBase)
		{
			double SQRT = (mNewPosition - mSpawnPosition).SizeSquared2D();
			if (SQRT < mDistanceSQRT)
			{
				mDistanceSQRT = SQRT;
			}
			else
			{
				mDistanceSQRT = BIG_NUMBER;
				mGoBackToBase = false;

				SetNewRotation(GetActorForwardVector());
				mCurrentVelocity = FVector::ZeroVector;
			}
		}
		SetActorLocation(mNewPosition);
	}
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::OnHitCallback(AActor* apDamagedActor, float aDamage, const UDamageType* apDamageType,
	AController* apInstigatedBy, AActor* apDamageCauser)
{
	mHealth -= aDamage;
	ScreenD(Format1("Damage: %f", aDamage));
	if (mHealth <= 0.0f)
	{
		Destroy();
	}
}

