#include "ProjectileBullet.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterUnreal/Public/Utils.h"

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
	apSphereComponent->IgnoreActorWhenMoving(mpOwnerCharacter, true);
	apSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBullet::BeginOverlapCallback);
}

void AProjectileBullet::BeginOverlapCallback(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ScreenD(Format1("%s", *HitResult.GetActor()->GetName()));
	UGameplayStatics::ApplyDamage(OtherActor, mDamage, mpOwnerCharacter->GetController(), GetOwner(), {});
	Destroy();
}

// Called every frame
void AProjectileBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z <= 0)
	{
		Destroy();
	}
}

