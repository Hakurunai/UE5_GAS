// Copyright Hakurunai

#include "AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Aura/Characters/AuraCharacter.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	AuraCharacter = nullptr;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();	
	
	//We want to crash early if something is wrong with the input, or player can launch a game he cannot play
	check(AuraContext);
	
	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//We want to crash here if something is wrong
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	//Callback
	{
		//Movement
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

		//Camera
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::CameraZoom);
	}	
}

void AAuraPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AuraCharacter = Cast<AAuraCharacter>(GetCharacter());
	check(AuraCharacter);
	CameraZoomData.DefaultDistance = AuraCharacter->GetCurrentCameraDistance();
	CameraZoomData.CurrentDistance = CameraZoomData.DefaultDistance;
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
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

void AAuraPlayerController::CameraZoom(const FInputActionValue& InputActionValue)
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
	//Apply new distance computed to the camera boom
	auto PlayerChara = Cast<AAuraCharacter>(GetCharacter());
	if (!PlayerChara)
		return;
	
	PlayerChara->UpdateCameraDistance(Data.CurrentDistance);	
}