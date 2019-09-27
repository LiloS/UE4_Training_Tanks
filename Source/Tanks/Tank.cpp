// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/ArrowComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "TankStatics.h"
#include "ConstructorHelpers.h"

void FTankInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}

void FTankInput::MoveX(float AxisValue)
{
	RawMovementInput.X += AxisValue;
}

void FTankInput::MoveY(float AxisValue)
{
	RawMovementInput.Y += AxisValue;
}

void FTankInput::Fire1(bool bPressed)
{
	bFire1 = bPressed;
}

void FTankInput::Fire2(bool bPressed)
{
	bFire2 = bPressed;
}

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TankBase"));
	}

	TankDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TankDirection"));
	TankDirection->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TankSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TankSprite"));
	TankSprite->AttachToComponent(TankDirection, FAttachmentTransformRules::KeepRelativeTransform);

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprignArm"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TankCamera"));
	CameraComponent->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	CameraComponent->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 1024.0f;
	CameraComponent->AspectRatio = 3.0f / 4.0f;


	ChildTurrel = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turrel"));
	ChildTurrel->AttachToComponent(TankDirection, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankInput.Sanitize();
	// log
	UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), TankInput.MovementInput.X, TankInput.MovementInput.Y);

	{
		FVector DesiredMovementDirection = FVector(TankInput.MovementInput.X, TankInput.MovementInput.Y, 0);
		if (!DesiredMovementDirection.IsNearlyZero())
		{
			FRotator MovementAngle = DesiredMovementDirection.Rotation();
			float DeltaYaw = UTankStatics::FindDeltaAngleDegrees(TankDirection->GetComponentRotation().Yaw,
			                                                     MovementAngle.Yaw);

			auto bReverse = false;
			if (DeltaYaw != 0.0f)
			{
				auto AdjustedYaw = DeltaYaw;

				if (AdjustedYaw < -90.0f)
				{
					AdjustedYaw += 180.0f;
					bReverse = true;
				}
				else if (AdjustedYaw > 90.0f)
				{
					AdjustedYaw -= 180.0f;
					bReverse = true;
				}

				float MaxYawThisFrame = YawSpeed * DeltaTime;

				if (MaxYawThisFrame >= FMath::Abs(AdjustedYaw))
				{
					if (bReverse)
					{
						FRotator FacingAngle = MovementAngle;
						FacingAngle.Yaw = MovementAngle.Yaw + 180.0f;
						TankDirection->SetWorldRotation(FacingAngle);
					}
					else
					{
						TankDirection->SetWorldRotation(MovementAngle);
					}
				}
				else
				{
					TankDirection->AddLocalRotation(FRotator(0.0f, FMath::Sign(AdjustedYaw) * MaxYawThisFrame, 0.0f));
				}

				// Move the tank
			}

			{
				FVector MovementDirection = TankDirection->GetForwardVector() * (bReverse ? -1.0f : 1.0f);
				auto Pos = GetActorLocation();

				Pos.X += MovementDirection.X * MoveSpeed * DeltaTime;
				Pos.Y += MovementDirection.Y * MoveSpeed * DeltaTime;

				UE_LOG(LogTemp, Warning, TEXT("FINAL: (%f %f)"), MovementDirection.X, MovementDirection.Y);


				SetActorLocation(Pos);
			}
		}
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &ATank::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATank::MoveY);
	InputComponent->BindAction("Fire1", IE_Pressed, this, &ATank::Fire1Pressed);
	InputComponent->BindAction("Fire1", IE_Released, this, &ATank::Fire1Released);
	InputComponent->BindAction("Fire2", IE_Pressed, this, &ATank::Fire2Pressed);
	InputComponent->BindAction("Fire2", IE_Released, this, &ATank::Fire2Released);
}

const FTankInput& ATank::GetCurrentInput()
{
	return TankInput;
}

void ATank::MoveX(float AxisValue)
{
	TankInput.MoveX(AxisValue);
}

void ATank::MoveY(float AxisValue)
{
	TankInput.MoveY(AxisValue);
}

void ATank::Fire1Pressed()
{
	TankInput.Fire1(true);
}

void ATank::Fire1Released()
{
	TankInput.Fire1(false);
}

void ATank::Fire2Pressed()
{
	TankInput.Fire2(true);
}

void ATank::Fire2Released()
{
	TankInput.Fire2(false);
}
