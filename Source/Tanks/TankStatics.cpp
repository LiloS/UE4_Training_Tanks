// Fill out your copyright notice in the Description page of Project Settings.


#include "TankStatics.h"

float UTankStatics::FindDeltaAngleDegrees(float A1, float A2)
{
	int arraySize = 7;
	float Delta = A2 - A1;

	if (Delta > 180.0f)
	{
		Delta -= 360.0f;
	}
	else if (Delta < -180.0f)
	{
		Delta += 360.0f;
	}

	return Delta;
}

bool UTankStatics::FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle)
{
	auto Normal = (Target - Start).GetSafeNormal();

	if (!Normal.IsNearlyZero())
	{
		Angle = FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.X));
		return true;
	}

	return false;
}
