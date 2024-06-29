// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "CameraZoomData.generated.h"

USTRUCT(BlueprintType)
struct FCameraZoomData
{
	GENERATED_USTRUCT_BODY()
	
	FCameraZoomData() : DefaultDistance(1000), CurrentDistance(0), IntervalLength(200), InterpSpeed(2.f),
	CurrentZoomInterval(0), MaxZoomIntervalNumber(4), UpdateRate(0.01f) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float DefaultDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Zoom)
	float CurrentDistance;

	//Distance moved per interval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float IntervalLength;

	//Time needed to do the zoom/unzoom action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float InterpSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Zoom)
	int32 CurrentZoomInterval;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	uint8 MaxZoomIntervalNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float UpdateRate;
	
	FTimerHandle TimerHandle;
};