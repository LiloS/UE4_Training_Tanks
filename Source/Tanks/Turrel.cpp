// Fill out your copyright notice in the Description page of Project Settings.


#include "Turrel.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TankStatics.h"
#include "Missile.h"

// Sets default values
ATurrel::ATurrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurrelDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurrelDirection"));
	RootComponent = TurrelDirection;

	TurrelSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TurrelSprite"));
	TurrelSprite->AttachToComponent(TurrelDirection, FAttachmentTransformRules::KeepRelativeTransform);
	
	YawSpeed = 180.0f;
}

// Called when the game starts or when spawned
void ATurrel::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(GetParentComponent()->GetOwner());
	check(Tank);
}

// Called every frame
void ATurrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(TurrelDirection);

	if (Tank)
	{
		if (APlayerController* PC = Cast<APlayerController>(Tank->GetController()))
		{
			FVector2D AimLocation;

			if (PC->GetMousePosition(AimLocation.X, AimLocation.Y))
			{
				auto TurrelLocation = FVector2D::ZeroVector;
				UGameplayStatics::ProjectWorldToScreen(PC, TurrelDirection->GetComponentLocation(), TurrelLocation);

				float DesiredYaw;

				if (UTankStatics::FindLookAtAngle2D(TurrelLocation, AimLocation, DesiredYaw))
				{
					FRotator CurrentRotation = TurrelDirection->GetComponentRotation();
					auto DeltaYaw = UTankStatics::FindDeltaAngleDegrees(CurrentRotation.Yaw, DesiredYaw);
					auto MaxDeltaYawThisFrame = YawSpeed * DeltaTime;

					if (MaxDeltaYawThisFrame >= FMath::Abs(DeltaYaw))
					{
						CurrentRotation.Yaw = DesiredYaw;
					}
					else
					{
						CurrentRotation.Yaw += FMath::Sign(DeltaYaw) * MaxDeltaYawThisFrame;
					}

					TurrelDirection->SetWorldRotation(CurrentRotation);
				}
			}

			auto CurrentInput = Tank->GetCurrentInput();
			if (CurrentInput.bFire1 && Projectile)
			{
				if (auto World = GetWorld())
				{
					UE_LOG(LogTemp, Warning, TEXT("FIRE!"));

					if (AMissile* NewProjectile = Cast<AMissile>(World->SpawnActor(Projectile)))
					{
						auto Loc = TurrelSprite->GetSocketLocation("Muzzle");
						auto Rot = TurrelDirection->GetComponentRotation();
						
						NewProjectile->SetActorLocation(Loc);
						NewProjectile->SetActorRotation(Rot);
					}
					
				}
			}
		}
	}
}
