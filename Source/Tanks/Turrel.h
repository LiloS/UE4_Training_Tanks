// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "Turrel.generated.h"

class AMissile;
UCLASS()
class TANKS_API ATurrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurrel();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Max turn rate.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turrel")
	float YawSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turrel")
	class ATank* Tank;

	// Missile.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turrel")
		TSubclassOf<AMissile> Projectile;

	// Reload speed in seconds.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turrel")
		float ReloadSpeed;

private:
	bool ReadyToFire;
	void Reload();

public:

	// Called every frame
	void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turrel", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* TurrelDirection;

	// Sprite for the Turrel body.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turrel", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* TurrelSprite;
};
