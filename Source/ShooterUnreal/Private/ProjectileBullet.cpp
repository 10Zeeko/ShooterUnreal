// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBullet.h"

// Sets default values
AProjectileBullet::AProjectileBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	apSphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletModel"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	this->apSphereComponent->SetStaticMesh(SphereMeshAsset.Object);
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

