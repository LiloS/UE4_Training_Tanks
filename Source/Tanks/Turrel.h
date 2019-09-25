// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turrel.generated.h"

UCLASS()
class TANKS_API ATurrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turrel", meta = (AllowPrivateAccess = "true"))
	class	UArrowComponent* TurrelDirection;

	// Sprite for the Turrel body.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turrel", meta = (AllowPrivateAccess = "true"))
	class	UPaperSpriteComponent* TurrelSprite;
};
