// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "rgShooterGameModeBase.h"

#include "PlayerCharacter.h"
#include "FpHUD.h"
#include "UObject/ConstructorHelpers.h"

ArgShooterGameModeBase::ArgShooterGameModeBase()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_FpCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AFpHUD::StaticClass();
}
