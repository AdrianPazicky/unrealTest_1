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

UCLASS()
class UNREALTEST_1_API ASCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, Category = "PrimaryAttack_Class");
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "SecondAttack_Class");
	TSubclassOf<AActor> ProjectileClass2;
	UPROPERTY(EditAnywhere, Category = "ThirdAttack_Class");
	TSubclassOf<AActor> ProjectileClass3;

	UPROPERTY(EditAnywhere, Category = "PrimaryAttack_Anim");
	UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere, Category = "SecondAttack_Anim");
	UAnimMontage* AttackAnim2;
	UPROPERTY(EditAnywhere, Category = "ThirdAttack_Anim");
	UAnimMontage* AttackAnim3;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondAttack;
	FTimerHandle TimerHandle_ThirdAttack;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	USAttributeComponent* AttributeComp;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void SecondAttack();
	void SecondAttack_TimeElapsed();
	void ThirdAttack();
	void ThirdAttack_TimeElapsed();
	void PrimaryInteract();


	//void Jump();

public:	
	UFUNCTION()
	void TeleportToProjectile(AActor* Actor);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
