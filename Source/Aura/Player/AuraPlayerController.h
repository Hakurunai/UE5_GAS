// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Camera/CameraZoomData.h"
#include "../Camera/CameraRotationData.h"
#include "AuraPlayerController.generated.h"

class UInputDataConfig;
struct FInputActionValue;
class UInputMappingContext;
class AAuraCharacter;
class IHighlightable;

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
	virtual void PlayerTick(float DeltaTime) override;
	
private :
#pragma region Action Callbacks
	UFUNCTION()
	void ActionMoveCallback(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void ActionCameraZoomCallback(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void ActionCameraRotationCallback(const FInputActionValue& InputActionValue);
#pragma endregion Action Callbacks

#pragma region Camera functions
	void UpdateCameraZoom(const float DesiredDistance, FCameraZoomData& Data) const;

	void AdjustInitialCameraRotation();
#pragma endregion Camera Functions

#pragma region Camera Datas
	UPROPERTY(EditAnywhere, Category = Camera)
	FCameraZoomData CameraZoomData;

	UPROPERTY(EditAnywhere, Category = Camera)
	FCameraRotationData CameraRotationData;
#pragma endregion Camera Datas

#pragma region Cursor Trace functions
	void CursorTrace();
#pragma endregion Cursor Trace functions

#pragma region Cursor Trace Datas
	TScriptInterface<IHighlightable> LastActor;	
	TScriptInterface<IHighlightable> CurrentActor;
#pragma endregion Cursor Trace Datas

#pragma region Input Datas
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> ContextAura;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputDataConfig> InputDataActions;
#pragma endregion Input Datas
	
	UPROPERTY()
	TWeakObjectPtr<AAuraCharacter> AuraCharacter;
};