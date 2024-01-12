// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SHOOTERUNREAL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHitCallback(AActor* apDamagedActor, float aDamage, const UDamageType* apDamageType, AController* apInstigatedBy, AActor* apDamageCauser);
	
	AEnemyCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* mpBoxCollision;

	UPROPERTY(EditDefaultsOnly)
	float mMoveSpeed {600.0f};

	UPROPERTY(EditDefaultsOnly)
	float mHealth {10.0f};

	UPROPERTY(EditDefaultsOnly)
	float mDamage {5.0f};

#pragma region IA

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* mAIPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* mAISight;

	UFUNCTION()
	void OnSenseCallback(const TArray<AActor*>& aUpdateActor);
	
#pragma endregion

protected:
	virtual void BeginPlay() override;
private:
	void SetNewRotation(const FVector& aTargetRot);

	UPROPERTY(VisibleAnywhere)
	FRotator mCurrentRotation;

	UPROPERTY(VisibleAnywhere)
	FVector mSpawnPosition;

	UPROPERTY(VisibleAnywhere)
	FVector mCurrentVelocity;

	bool mGoBackToBase;
	FVector mNewPosition;
	float mDistanceSQRT;
};
