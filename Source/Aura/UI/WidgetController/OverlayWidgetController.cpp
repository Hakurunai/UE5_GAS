// Copyright Hakurunai


#include "OverlayWidgetController.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	const UAuraAttributeSet* attributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(attributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(attributeSet->GetMaxHealth());
}
