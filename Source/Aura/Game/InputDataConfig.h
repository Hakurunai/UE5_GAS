// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"


class UInputAction;

UCLASS(BlueprintType)
class AURA_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ActionMove;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ActionCameraZoom;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ActionCameraRotation;
};
