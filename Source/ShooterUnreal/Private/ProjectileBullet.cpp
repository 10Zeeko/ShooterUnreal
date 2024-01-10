#include "ProjectileBullet.h"

// Sets default values
AProjectileBullet::AProjectileBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	apSphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletModel"));
	apProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial>BulletSphereMaterial(TEXT("Material'/Engine/VREditor/UI/KeyDiskMaterial.KeyDiskMaterial'"));
	this->apSphereComponent->SetStaticMesh(SphereMeshAsset.Object);
	this->apSphereComponent->SetMaterial(0, BulletSphereMaterial.Object);
	apProjectileMovementComponent->InitialSpeed = 2000.0f;
	apProjectileMovementComponent->MaxSpeed = 2000.0f;
}

// Called when the game starts or when spawned
void AProjectileBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

