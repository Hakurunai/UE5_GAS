// Copyright Hakurunai


#include "OverlayWidgetController.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	const UAuraAttributeSet* attributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(attributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(attributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(attributeSet->GetMana());
	OnMaxManaChanged.Broadcast(attributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* attributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		attributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	attributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	attributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	attributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}