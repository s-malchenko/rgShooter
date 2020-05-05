#pragma once

#include "CoreMinimal.h"
#include "FpHUD.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RGSHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	AFpHUD* fpHud;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FpMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FpCamera;

	UPROPERTY(VisibleAnywhere)
	uint16 WeaponSlotCount = 2;

	TArray<AWeaponBase*> weapons;
	AWeaponBase* currentWeapon;
	uint16 currentWeaponSlot;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handles moving forward/backward
	void MoveForward(float val);

	// Handles strafing movement, left and right
	void MoveRight(float val);

	void EquipNextWeapon();
	void EquipPrevWeapon();
	void EquipWeapon(uint16 slotIndex);

	// Handles fire of current weapon, if equipped
	void PrimaryFire();
	void SecondaryFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
