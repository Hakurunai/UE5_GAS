// Copyright Hakurunai

#include "Enemy.h"
#include "Aura/Aura.h"

AEnemy::AEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AEnemy::HighLightActor()
{
	auto mesh = GetMesh();
	mesh->SetRenderCustomDepth(true);
	mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemy::UnHighLightActor()
{
	auto mesh = GetMesh();
	mesh->SetRenderCustomDepth(false);
	mesh->SetCustomDepthStencilValue(0);

	Weapon->SetRenderCustomDepth(false);
	Weapon->SetCustomDepthStencilValue(0);
}