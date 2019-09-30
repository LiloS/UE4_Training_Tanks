// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBrains.h"
#include "Zombie.h"

void AZombieBrains::Tick(float DeltaTime)
{
	if (PawnAsZombie)
	{
		if (AActor* Target = PawnAsZombie->GetTarget())
		{
			auto DirectionToTarget = (Target->GetActorLocation() - PawnAsZombie->GetActorLocation()).GetSafeNormal2D();
			auto DotToTarget = FVector::DotProduct(DirectionToTarget, PawnAsZombie->GetActorForwardVector());
			auto SidewaysDotToTarget = FVector::DotProduct(DirectionToTarget, PawnAsZombie->GetActorRightVector());
			auto DeltaYawDesired = FMath::Atan2(SidewaysDotToTarget, DotToTarget);

			if (PawnAsZombie->ZombieAIShouldAttack())
			{
				PawnAsZombie->AddAttackInput();
			}
			else
			{
				PawnAsZombie->AddMovementInput(FVector(1.0f, 0.0f, 0.0f),
					FMath::GetMappedRangeValueClamped(
						FVector2D(-0.707f, 0.707f), FVector2D(0.0f, 1.0f), DotToTarget));
				PawnAsZombie->AddRotationInput(DeltaYawDesired);
			}
		}
	}
}

void AZombieBrains::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PawnAsZombie = Cast<AZombie>(GetPawn());
}

void AZombieBrains::OnUnPossess()
{
	Super::OnUnPossess();
	PawnAsZombie = nullptr;
}
