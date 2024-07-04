// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "CameraRotationData.generated.h"

USTRUCT(BlueprintType)
struct FCameraRotationData
{
	GENERATED_USTRUCT_BODY()

	FCameraRotationData() : YawRotationSensibility(1.f), PitchRotationSensibility(1.f), PitchMin(290.f), PitchMax(315.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta = (ClampMin = 0.1f, ClampMax = 2.f, UIMin = 0.1f, UIMax = 2.f))
	float YawRotationSensibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta = (ClampMin = 0.1f, ClampMax = 2.f, UIMin = 0.1f, UIMax = 2.f))
	float PitchRotationSensibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float PitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float PitchMax;
};