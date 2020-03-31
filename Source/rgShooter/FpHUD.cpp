#include "FpHUD.h"

#include "Engine/Canvas.h"

void AFpHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
}

void AFpHUD::DrawCrosshair()
{
	FVector2D screenCenter(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	const float minGap = 5;
	const float maxGap = 80;
	const float thickness = 2;
	const float size = 8;
	FLinearColor color = FLinearColor::Green;

	auto gap = CrosshairSpread * 6;
	gap = FMath::Clamp(gap, minGap, maxGap);

	FVector2D lineStart = screenCenter + FVector2D(0, gap);
	FVector2D lineEnd = lineStart + FVector2D(0, size);
	Canvas->K2_DrawLine(lineStart, lineEnd, thickness, color);

	lineStart = screenCenter + FVector2D(0, -gap);
	lineEnd = lineStart + FVector2D(0, -size);
	Canvas->K2_DrawLine(lineStart, lineEnd, thickness, color);

	lineStart = screenCenter + FVector2D(gap, 0);
	lineEnd = lineStart + FVector2D(size, 0);
	Canvas->K2_DrawLine(lineStart, lineEnd, thickness, color);

	lineStart = screenCenter + FVector2D(-gap, 0);
	lineEnd = lineStart + FVector2D(-size, 0);
	Canvas->K2_DrawLine(lineStart, lineEnd, thickness, color);
}
