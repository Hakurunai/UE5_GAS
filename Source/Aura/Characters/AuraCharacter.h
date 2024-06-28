// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public ACharacterBase
{
	GENERATED_BODY()

public :
	AAuraCharacter();
	
	UFUNCTION(BlueprintCallable, Category = Camera)
	FORCEINLINE void UpdateCameraDistance(const float Distance) {CameraBoom->TargetArmLength = Distance;}

	UFUNCTION(BlueprintCallable, Category = Camera)
	FORCEINLINE float GetCurrentCameraDistance() const {return CameraBoom->TargetArmLength;}
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;
};
