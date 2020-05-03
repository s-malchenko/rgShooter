#include "WeaponBase.h"

#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
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

