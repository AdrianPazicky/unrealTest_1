// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASTeleportProjectile::ASTeleportProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(("SphereComp"));
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->SetSimulatePhysics(false);
	SphereComp->SetEnableGravity(false);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(("EffectComp"));
	EffectComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(("MovementComp"));
	MovementComp->InitialSpeed = 3000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;  // Disable gravity for the projectile
}

// Called when the game starts or when spawned
void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(LifetimeTimerHandle, this, &ASTeleportProjectile::OnLifetimeExpired, Lifetime, false);
}
void ASTeleportProjectile::OnLifetimeExpired()
{
	Destroy();
}

// Called every frame
void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

