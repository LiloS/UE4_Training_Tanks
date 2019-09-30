// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Zombie.generated.h"

class ATank;
class UCameraShake;

UCLASS()
class TANKS_API AZombie : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	AActor* GetTarget();
	
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category="AI")
	ATank* GetTargetAsTank();

	UFUNCTION(BlueprintNativeEvent, Category="AI")
	bool ZombieAIShouldAttack();
	virtual bool ZombieAIShouldAttack_Implementation();

	UFUNCTION(BlueprintCallable, Category="Pawn|Input", meta = (Keywords = "AddInput"))
	virtual void AddRotationInput(float DeltaYawDesired);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "GetInput"))
	virtual	float GetRotationInput();

	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "GetInput"))
		virtual	float ConsumeRotationInput();

	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "AddInput"))
	virtual void AddAttackInput();

	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "GetInput"))
		virtual	float GetAttackInput();

	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "GetInput"))
		virtual	float ConsumeAttackInput();

private:

	UPROPERTY(VisibleInstanceOnly, Category="AI")
	AActor* TargetActor;

	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	ATank* TargetTank;
	
protected:

	// Camera shake when zombie hits tank.
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShake> HitShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Zombie", meta = (ClampMin="1.0"))
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float SightDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float SightAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float YawSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float AttackAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
	float AttackCooldown;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "Zombie")
	float AttackAvailableTime;
};
