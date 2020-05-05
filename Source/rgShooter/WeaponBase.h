#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class RGSHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* MuzzleLocation;

	UPROPERTY(EditAnywhere, Category = Name)
	FName SocketName;

	// Spawns meshes to debug fire actions
	void DebugFire(bool secondary);
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	USkeletalMeshComponent* GetMesh();
	const FName& GetSocketName() const;
	FVector GetMuzzleAbsoluteLocation();

	void Equip();
	void Unequip();
	void TryFire(bool secondary = false);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
