#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FpHUD.generated.h"

UCLASS()
class RGSHOOTER_API AFpHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawCrosshair();

public:
	float CrosshairSpread;
};
