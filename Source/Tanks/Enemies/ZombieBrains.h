// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieBrains.generated.h"


class AZombie;
/**
 * 
 */
UCLASS()
class TANKS_API AZombieBrains : public AAIController
{
	GENERATED_BODY()

public:

	void Tick(float DeltaTime) override;

	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Zombie")
	AZombie* PawnAsZombie;
};
