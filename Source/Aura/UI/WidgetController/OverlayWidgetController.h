// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"


struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOneFloatChangedDelegate, float, NewValue);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public :
	virtual void BroadCastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnOneFloatChangedDelegate OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnOneFloatChangedDelegate OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnOneFloatChangedDelegate OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnOneFloatChangedDelegate OnMaxManaChanged;

protected :
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};