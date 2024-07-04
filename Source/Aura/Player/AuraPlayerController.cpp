// Copyright Hakurunai

#include "AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Aura/Characters/AuraCharacter.h"
#include "../Camera/CameraZoomData.h"
#include "Aura/Game/InputDataConfig.h"
#include "Aura/Interaction/Highlightable.h"
#include "Aura/Utilities/Print.h"
#include "Kismet/GameplayStatics.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	AuraCharacter = nullptr;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();	
	
	//We want to crash early if something is wrong with the input, or player can launch a game he cannot play
	check(ContextAura);
	
	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(ContextAura, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	//Called it here cause OnPossess could be called on a non completely initialized character
	AuraCharacter = Cast<AAuraCharacter>(GetCharacter());
	check(AuraCharacter.IsValid());
	AdjustInitialCameraRotation();

	auto CamManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CamManager->ViewPitchMin = CameraRotationData.PitchMin;
	CamManager->ViewPitchMax = CameraRotationData.PitchMax;
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//We want to crash here if something is wrong
	UEnhancedInputComponent* Inputs = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	//Callback
	{
		//Movement
		Inputs->BindAction(InputDataActions->ActionMove, ETriggerEvent::Triggered, this, &AAuraPlayerController::ActionMoveCallback);

		//Camera
		Inputs->BindAction(InputDataActions->ActionCameraZoom, ETriggerEvent::Triggered, this, &AAuraPlayerController::ActionCameraZoomCallback);
		Inputs->BindAction(InputDataActions->ActionCameraRotation, ETriggerEvent::Triggered, this, &AAuraPlayerController::ActionCameraRotationCallback);
	}	
}

void AAuraPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	AuraCharacter = Cast<AAuraCharacter>(GetCharacter());	
	check(AuraCharacter.IsValid());
	CameraZoomData.DefaultDistance = AuraCharacter->GetCurrentCameraDistance();
	CameraZoomData.CurrentDistance = CameraZoomData.DefaultDistance;

	AdjustInitialCameraRotation();
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::ActionMoveCallback(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();	

	//controller is facing camera, while pawn rotation is in world
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	//Move pawn
	if (auto ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::ActionCameraZoomCallback(const FInputActionValue& InputActionValue)
{
	const auto InputValue = InputActionValue.Get<float>();
	auto& Data = CameraZoomData;
	
	//Update current interval, need to be clamped by -maxInter and + maxInter
	Data.CurrentZoomInterval += InputValue;
	Data.CurrentZoomInterval = FMath::Clamp(Data.CurrentZoomInterval, -Data.MaxZoomIntervalNumber, Data.MaxZoomIntervalNumber);
	
	//Compute new desired position
	auto DesiredDistance = Data.DefaultDistance + Data.CurrentZoomInterval * Data.IntervalLength;
	if (FMath::IsNearlyEqual(DesiredDistance, Data.CurrentDistance))
		return;
	
	//Clear the TimerHandle and start another one to interpolate camera movement
	//The timer will loop
	auto& TimerManager = GetWorldTimerManager();
	TimerManager.ClearTimer(Data.TimerHandle);
	TimerManager.SetTimer
	(
		Data.TimerHandle,
		[this, DesiredDistance, &Data]()
		{
			UpdateCameraZoom(DesiredDistance, Data);
		},
		Data.UpdateRate,
		true
	);
}

void AAuraPlayerController::UpdateCameraZoom(const float DesiredDistance, FCameraZoomData& Data) const
{
	static float Tolerance = 1.f;
	Data.CurrentDistance = FMath::FInterpTo(Data.CurrentDistance, DesiredDistance, Data.UpdateRate, Data.InterpSpeed);
	
	//Stop condition
	if (FMath::IsNearlyEqual(DesiredDistance, Data.CurrentDistance, Tolerance))
	{
		Data.CurrentDistance = DesiredDistance;
		GetWorldTimerManager().ClearTimer(Data.TimerHandle);
	}	
	AuraCharacter->UpdateCameraDistance(Data.CurrentDistance);	
}

void AAuraPlayerController::AdjustInitialCameraRotation()
{
	SetControlRotation(AuraCharacter->GetCameraBoom()->GetRelativeRotation());
	AuraCharacter->GetCameraBoom()->bInheritPitch = true;	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor(); //TScriptInterface will check the interface type for us

	/*
	 * Line trace from cursors scenario
	 * 1- LastActor is null and CurrentActor is null
	 *		-> Do nothing
	 * 2- LastActor is null and CurrentActor is valid
	 *		-> Highlight CurrentActor
	 * 3- LastActor is valid and CurrentActor is null
	 *		-> UnHighlight LastActor
	 * 4- Both actors are valid but last and current are different
	 *		-> UnHighlight LastActor and Highlight CurrentActor
	 * 5- Both actors are valid and they are the same
	 *		-> Do nothing
	 */

	if (LastActor == nullptr)
	{
		if (CurrentActor != nullptr) //Case 2
			CurrentActor->HighLightActor();
		// else = Case 1 -> DO NOTHING
	}
	else //LastActor is valid
	{
		if (CurrentActor == nullptr) //Case 3
			LastActor->UnHighLightActor();
		else //Both actors are valid
		{
			if (LastActor != CurrentActor) //Case 4
			{
				LastActor->UnHighLightActor();
				CurrentActor->HighLightActor();
			}
			//else = Case 5 -> DO NOTHING
		}
	}
}

void AAuraPlayerController::ActionCameraRotationCallback(const FInputActionValue& InputActionValue)
{
	//Rotate around the character
	const auto InputValue = InputActionValue.Get<FVector2d>();
	AddYawInput(InputValue.X * CameraRotationData.YawRotationSensibility);
	AddPitchInput(InputValue.Y * CameraRotationData.PitchRotationSensibility);
}