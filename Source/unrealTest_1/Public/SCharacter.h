// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;
class USActionComponent;

UCLASS()
class UNREALTEST_1_API ASCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, Category = "PrimaryAttack_Class");
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "BlackholeAttack_Class");
	TSubclassOf<AActor> BlackHoleProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Dash_Class");
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "PrimaryAttack_Anim");
	UAnimMontage* AttackAnim;


	UPROPERTY(EditAnywhere, Category = "Delay")
	float AttackAnimDelay;

	FTimerHandle TimerHandle_PrimaryAttack; 
	FTimerHandle TimerHandle_BlackholeAttack;
	FTimerHandle TimerHandle_Dash;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere);
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere);
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	USActionComponent* ActionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();
	void Dash();
	void Dash_TimeElapsed();
	void PrimaryInteract();
	void SprintStart();
	void SprintStop();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

	//void Jump();

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
