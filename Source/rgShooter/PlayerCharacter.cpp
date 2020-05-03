#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "FpHUD.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(30.f, 70.f);

	FpCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FpCamera"));
	FpCamera->SetupAttachment(GetCapsuleComponent());
	FpCamera->SetRelativeLocation(FVector(-20, 0, 50));
	FpCamera->bUsePawnControlRotation = true;

	FpMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FpMesh"));
	FpMesh->SetOnlyOwnerSee(true);
	FpMesh->SetupAttachment(FpCamera);
	FpMesh->bCastDynamicShadow = false;
	FpMesh->CastShadow = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	fpHud = StaticCast<AFpHUD*>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	if (!fpHud)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find HUD!"));
	}

	weapons.AddDefaulted(WeaponSlotCount);
}

void APlayerCharacter::MoveForward(float Val)
{
	if (Val != 0)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void APlayerCharacter::MoveRight(float val)
{
	if (val != 0)
	{
		AddMovementInput(GetActorRightVector(), val);
	}
}

void APlayerCharacter::EquipNextWeapon()
{
	auto slotToEquip = currentWeaponSlot;

	if (++slotToEquip >= weapons.Num())
	{
		slotToEquip = 0;
	}

	EquipWeapon(slotToEquip);
}

void APlayerCharacter::EquipPrevWeapon()
{
	auto slotToEquip = currentWeaponSlot;

	if (slotToEquip > 0)
	{
		--slotToEquip;
	}
	else
	{
		slotToEquip = weapons.Num() - 1;
	}

	EquipWeapon(slotToEquip);
}

void APlayerCharacter::EquipWeapon(uint16 slotIndex)
{
	if (slotIndex + 1 > weapons.Num())
	{
		slotIndex = weapons.Num() - 1;
	}

	UE_LOG(LogTemp, Warning, TEXT("Trying to equip weapon slot %d"), slotIndex);

	currentWeaponSlot = slotIndex;
	currentWeapon = weapons[slotIndex];

	if (currentWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon slot %d equipped"), slotIndex);
		currentWeapon->GetMesh()->SetupAttachment(FpMesh, currentWeapon->GetSocketName());
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (fpHud)
	{
		// TODO use weapon spread instead of velocity
		fpHud->CrosshairSpread = GetVelocity().Size() / 100;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Bind mouse look
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Bind weapon changing
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &APlayerCharacter::EquipNextWeapon);
	PlayerInputComponent->BindAction("PrevWeapon", IE_Pressed, this, &APlayerCharacter::EquipPrevWeapon);
}

