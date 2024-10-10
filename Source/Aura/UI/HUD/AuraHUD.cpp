// Copyright Hakurunai

#include "AuraHUD.h"

#include "Aura/UI/Widget/AuraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "../WidgetController/OverlayWidgetController.h"

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class not initialized in BP_HUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class not initialized in BP_HUD"));

	//Creating our widget and widget controller
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(widget);

	const FWidgetControllerParams wc_Params(PC, PS, ASC, AS);
	OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	OverlayWidgetController->SetWidgetControllerParams(wc_Params);	
	OverlayWidgetController->BindCallbacksToDependencies();

	OverlayWidget->SetWidgetController(OverlayWidgetController);	
	OverlayWidgetController->BroadCastInitialValues();
	
	widget->AddToViewport();
}