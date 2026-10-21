#include "decls.h"
extern void FUN_00598e20();
extern void FUN_00598fc0(char param_1);
extern unsigned long DAT_05cda0bc;
extern struct NJS_TEXLIST DAT_02604ab8;
extern unsigned char DAT_05cda0b9;
extern unsigned short DAT_05cda0c0;
void FUN_00598dd0();
void FUN_005999c0(char *param_1);

// STUB: SADX 0x00598e20
void FUN_00598e20()
{
}

// STUB: SADX 0x00598ee0
short FadeIn()
{
	return (short)0;
}

// STUB: SADX 0x00598fc0
void FUN_00598fc0(char param_1)
{
}

// STUB: SADX 0x00598ff0
void InitFadeOut()
{
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
