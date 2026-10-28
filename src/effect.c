#include "decls.h"
void ___njColorBlendingMode(int tgt, int mode);
void late_DrawBoxFill2D(float x, float y, float x2, float y2, float pri, unsigned long argb, int flgs);
void FUN_00598fc0(char param_1);
void FUN_00598e20();
extern float ScreenRaitoX;
extern float ScreenRaitoY;
extern void ___njColorBlendingMode(int tgt, int mode);
extern void late_DrawBoxFill2D(float x, float y, float x2, float y2, float pri, unsigned long argb, int flgs);
extern void FUN_00598e20();
extern void FUN_00598fc0(char param_1);
extern unsigned long DAT_05cda0bc;
extern struct NJS_TEXLIST DAT_02604ab8;
extern unsigned char DAT_05cda0b9;
extern unsigned short DAT_05cda0c0;
void FUN_00598dd0();
void FUN_005999c0(char *param_1);

// FUNCTION: SADX 0x00598df0
void InitFadeIn()
{
	FUN_00598dd0();
	DAT_05cda0b9 = 5;
	DAT_05cda0c0 = 0x123;
	FUN_00598e20();
}

// FUNCTION: SADX 0x00598e20
void FUN_00598e20()
{
	unsigned char local_5i;
	float local_cj;
	int local_14;
	float local_10;
	if (DAT_05cda0c0 < 0xff)
	{
		local_14 = DAT_05cda0c0;
	}
	else
	{
		local_14 = 0xff;
	}
	local_5i = (unsigned char)local_14;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	FUN_00422560(7);
	local_10 = ScreenRaitoX * 640.0f;
	local_cj = ScreenRaitoY * 480.0f;
	late_DrawBoxFill2D(0.0f, 0.0f, local_10, local_cj, 22048.0f, (unsigned long)local_5i << 0x18, 1);
	FUN_00422560(1);
}

// STUB: SADX 0x00598ee0
short FadeIn()
{
	return (short)0;
}

// FUNCTION: SADX 0x00598fc0
void FUN_00598fc0(char param_1)
{
	union NJS_COLOR local_8;
	local_8.argb.b = (unsigned char)param_1;
	local_8.argb.g = 0;
	local_8.argb.r = 0;
	local_8.argb.a = 0;
	SetOffsetColor(&local_8);
}

// STUB: SADX 0x00598ff0
void InitFadeOut()
{
}

// STUB: SADX 0x00599030
short FadeOut()
{
	return (short)0;
}

// FUNCTION: SADX 0x00599140
void InitGameOver()
{
	FUN_00598dd0();
	DAT_05cda0c0 = 0;
	DAT_05cda0b9 = 1;
}

// FUNCTION: SADX 0x00599160
void EndGameOver()
{
	late_ReleaseTexture(&DAT_02604ab8);
	DAT_05cda0c0 = 0xff;
	DAT_05cda0b9 = 0;
}

// STUB: SADX 0x00599190
short GameOver(long sel)
{
	return (short)0;
}

// FUNCTION: SADX 0x005999b0
void SetOffsetColor(union NJS_COLOR *color)
{
	DAT_05cda0bc = color->color;
}

// FUNCTION: SADX 0x005999c0
void FUN_005999c0(char *param_1)
{
	if (param_1 != 0)
	{
		*(unsigned long *)param_1 = DAT_05cda0bc;
	}
}

// STUB: SADX 0x005999e0
void ColorOffset()
{
}
