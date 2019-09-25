// Fill out your copyright notice in the Description page of Project Settings.


#include "Turrel.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATurrel::ATurrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurrelDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurrelDirection"));
	RootComponent = TurrelDirection;

	TurrelSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TurrelSprite"));
	TurrelSprite->AttachToComponent(TurrelDirection, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ATurrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

