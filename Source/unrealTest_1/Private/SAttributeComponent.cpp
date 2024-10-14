// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"



// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	if (HealthMax <= 0.0f)
	{
		HealthMax = 100.0f;
	}
	//HealthMax = 100.0f;
	Health = HealthMax;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (GetOwner()->CanBeDamaged() == false)
	{
		return false;
	}

	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}
bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}
USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributesComp = GetAttributes(Actor);
	if (AttributesComp)
	{
		return AttributesComp->IsAlive();
	}
	return false;
}
