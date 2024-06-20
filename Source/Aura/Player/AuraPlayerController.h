// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class AAuraCharacter;

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

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public :
	AAuraPlayerController();

	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
private :
	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void CameraZoom(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void UpdateCameraZoom(const float DesiredDistance, FCameraZoomData& Data) const;

	UPROPERTY(EditAnywhere, Category = CameraZoom)
	FCameraZoomData CameraZoomData;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> CameraZoomAction;

	UPROPERTY()
	AAuraCharacter* AuraCharacter;
};