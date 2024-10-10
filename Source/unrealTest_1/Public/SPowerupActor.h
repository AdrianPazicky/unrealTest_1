// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerupActor.generated.h"

class USphereComponent;

UCLASS()
class UNREALTEST_1_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

protected:


	UPROPERTY(VisibleAnywhere, Category = "Powerup")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCoolDownPowerup();

	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

public:
	ASPowerupActor();

};
