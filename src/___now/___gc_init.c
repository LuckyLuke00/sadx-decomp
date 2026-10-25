#include "decls.h"
extern unsigned char DAT_05cda0a4;
extern int DAT_05cd14d4;
void FUN_004a27c0();
extern void gc_ClearScreen();

// FUNCTION: SADX 0x00598b80
void InitSystemTV()
{
	late_init();
	input_init();
}

// STUB: SADX 0x00598bd0
void Draw_Reset()
{
}

// FUNCTION: SADX 0x00598d20
void gc_ClearScreen()
{
	if ((char)DAT_05cda0a4 == 0)
	{
		return;
	}
	FUN_004a27c0();
	___njSetBackColor(0, 0, 0);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	ResetMaterial();
	ds_DrawBoxFill2D(0.0f, 0.0f, ScreenRaitoX * 640.0f, ScreenRaitoY * 480.0f, -1.0f, 0xff000000);
	DAT_05cd14d4 = 0;
}
