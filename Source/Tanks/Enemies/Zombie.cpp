// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"
#include "Camera/CameraShake.h"
#include "Tank.h"

// Sets default values
AZombie::AZombie()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = 100.0f;
	SightDistance = 500.0f;
	SightAngle = 60.0f;
	YawSpeed = 90.0f;
	WalkSpeed = 25.0f;
	RunSpeed = 45.0f;
	AttackDistance = 100.0f;
	AttackAngle = 30.0f;
	AttackCooldown = 1.0f;
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* AZombie::GetTarget()
{
	return TargetActor;
}

void AZombie::SetTarget(AActor* NewTarget)
{
	TargetActor = NewTarget;
	TargetTank = Cast<ATank>(NewTarget);
}

ATank* AZombie::GetTargetAsTank()
{
	return TargetTank;
}

void AZombie::AddAttackInput()
{
	bAttackInput = true;
}

bool AZombie::ZombieAI_Implementation()
{
	return true;
}

void AZombie::AddRotationInput(float DeltaYawDesired)
{
	YawInput += DeltaYawDesired;
}

float AZombie::GetRotationInput()
{
	return YawInput;
}

float AZombie::ConsumeRotationInput()
{
	auto RetVal = YawInput;
	YawInput = 0.0f;
	return RetVal;
}

float AZombie::GetAttackInput()
{
	return bAttackInput;
}

float AZombie::ConsumeAttackInput()
{
	auto bRetval = bAttackInput;
	bAttackInput = false;
	return bRetval;
}

bool AZombie::ZombieAIShouldAttack_Implementation()
{
	if (AActor* Target = GetTarget())
	{
		auto OurLocation = GetActorLocation();
		auto DirectionToTarget = (Target->GetActorLocation() - OurLocation).GetSafeNormal2D();
		auto DotToTarget = FVector::DotProduct(DirectionToTarget, GetActorForwardVector());
		if (DotToTarget >= FMath::Cos(FMath::DegreesToRadians(AttackAngle)))
		{
			auto DistSqXY = FVector::DistSquaredXY(Target->GetActorLocation(), OurLocation);
			if (DistSqXY <= (AttackDistance * AttackDistance))
			{
				return true;
			}
		}
	}
	return false;
}