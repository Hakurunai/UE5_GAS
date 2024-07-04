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
	
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
};