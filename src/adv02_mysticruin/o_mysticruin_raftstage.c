#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x006ad0e0
void fade_screen(float fade)
{
	float var1;
	float var2;
	int var3;

	if (DAT_05b9d838 == 0)
	{
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		var2 = ScreenRaitoY * 480.0f;
		var1 = ScreenRaitoX * 640.0f;
		var3 = (int)((1.0f - fade) * 255.0f);
		late_DrawBoxFill2D(0.0f, 0.0f, var1, var2, 22038.0f, (unsigned long)var3 << 0x18, 4);
	}
}

// STUB: SADX 0x006ad1d0
void FUN_006ad1d0(void *param_1)
{
}

// FUNCTION: SADX 0x006ad260
void FUN_006ad260(void)
{
	SetInputP(0, 0x18);
	SetPositionP(0, -110.0f, 65.0f, 1138.0f);
	SetRotationP(0, 0, 0x9800, 0);
}
