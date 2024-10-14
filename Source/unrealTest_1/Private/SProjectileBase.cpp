// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SAttributeComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	RootComponent = SphereComp;

	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block); // Zablokova? kolízie s hrá?mi a NPC
	SphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Blokova? kolízie s dynamickým svetom
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // Blokova? kolízie so statickým svetom
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(RootComponent);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 8000;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    AActor* MyActor = GetInstigator();
    if (!ensure(MyActor))
    {
        UE_LOG(LogTemp, Warning, TEXT("MyActor doesn't exist"));
        return;
    }

    // Make sure to log valid actors
    if (!OtherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("OtherActor is null"));
		Explode();
        return;
    }

    // Prevent self-hit detection
    if (MyActor == OtherActor) return;

    // Cast and apply damage if attribute component exists
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(OtherActor);
    if (AttributeComp)
    {
        AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
    }

    Explode();
}

void ASProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		Destroy();
	}
}

// Called when the game starts or when spawned
void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

