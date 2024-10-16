// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerup_HealthPotion.generated.h"

class UMeshComponent;

//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
UCLASS()
class UNREALTEST_1_API ASPowerup_HealthPotion : public ASPowerupActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASPowerup_HealthPotion();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UMeshComponent* MeshComp;
public:	
	void Interact_Implementation(APawn* InstigatorPawn) override;
};
