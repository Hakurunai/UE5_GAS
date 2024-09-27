// Copyright Hakurunai

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Aura/Interaction/Highlightable.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemy : public ACharacterBase, public IHighlightable
{
	GENERATED_BODY()

public :
	AEnemy();

	// Highlightable interface
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	// END Highlightable interface

protected :
	virtual void BeginPlay() override;
};