// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "../Camera/CameraZoomData.h"
#include "../Camera/CameraRotationData.h"
#include "AuraPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class AAuraCharacter;

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
	void ActionMoveCallback(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void ActionCameraZoomCallback(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void ActionCameraRotationCallback(const FInputActionValue& InputActionValue);
	
	void UpdateCameraZoom(const float DesiredDistance, FCameraZoomData& Data) const;

	void AdjustInitialCameraRotation();
	
	UPROPERTY(EditAnywhere, Category = Camera)
	FCameraZoomData CameraZoomData;

	UPROPERTY(EditAnywhere, Category = Camera)
	FCameraRotationData CameraRotationData;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> ContextAura;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ActionMove;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ActionCameraZoom;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ActionCameraRotation;

	UPROPERTY()
	TWeakObjectPtr<AAuraCharacter> AuraCharacter;
};