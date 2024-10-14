// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealthPotion.h"
#include "SAttributeComponent.h"

// Sets default values
ASPowerup_HealthPotion::ASPowerup_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ASPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{

	if (!ensure(InstigatorPawn)) return;
	
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		//Only activate if healed succesfully
		if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Potion Used"));
			HideAndCoolDownPowerup();
		}
	}
}

