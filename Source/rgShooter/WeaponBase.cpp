#include "WeaponBase.h"

#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

void AWeaponBase::DebugFire(bool secondary)
{
	UE_LOG(LogTemp, Warning, TEXT("Debug Pew"));
	auto color = secondary ? FColor::Magenta : FColor::Red;

	DrawDebugSphere(
		GetWorld(),
		GetMuzzleAbsoluteLocation(),
		10,
		8,
		color,
		false,
		0.03, // life time in sec
		0,
		5
	);

	// TODO this line shows the direction of weapon but not the bullet path
	auto lineStart = GetMuzzleAbsoluteLocation();
	auto lineEnd = lineStart - GetActorForwardVector() * 500;
	DrawDebugLine(
		GetWorld(),
		lineStart,
		lineEnd,
		color,
		false,
		5, // life time in sec
		0,
		2
	);
}

// Sets default values
AWeaponBase::AWeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	PrimaryActorTick.bCanEverTick = true;
}

USkeletalMeshComponent* AWeaponBase::GetMesh()
{
	return Mesh;
}

const FName& AWeaponBase::GetSocketName() const
{
	return SocketName;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Equip()
{
	SetActorHiddenInGame(false);
}

void AWeaponBase::Unequip()
{
	SetActorHiddenInGame(true);
}

void AWeaponBase::TryFire(bool secondary)
{
	DebugFire(secondary);
}

FVector AWeaponBase::GetMuzzleAbsoluteLocation()
{
	return GetActorLocation() + GetActorRotation().RotateVector(MuzzleLocation->GetRelativeLocation());
}

