// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class TANKS_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Projectile")
	void Explode();

	virtual void Explode_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float Speed;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Missile", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* MissileDirection;

	// Sprite for the Turrel body.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Missile", meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* MissileSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Missile", meta = (AllowPrivateAccess = "true"))
	class	UPaperFlipbookComponent* FlipbookComponent;
};
