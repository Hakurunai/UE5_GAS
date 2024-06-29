// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "CameraRotationData.generated.h"

USTRUCT(BlueprintType)
struct FCameraRotationData
{
	GENERATED_USTRUCT_BODY()

	FCameraRotationData() : YawRotationSpeed(400.f), PitchRotationSpeed(200.f), PitchMin(290.f), PitchMax(315.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float YawRotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float PitchRotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float PitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float PitchMax;
};