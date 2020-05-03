#include "WeaponBase.h"

#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;
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

