#include "EnemyCharacter.h"
#include  "Components/BoxComponent.h"
#include "Utils.h"
#include "ShooterUnreal/Public/Utils.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mpBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	mpBoxCollision->SetupAttachment(RootComponent);

	OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::OnHitCallback);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::OnHitCallback(AActor* apDamagedActor, float aDamage, const UDamageType* apDamageType,
	AController* apInstigatedBy, AActor* apDamageCauser)
{
	ScreenD(Format1("Damage: %f", aDamage));
}

