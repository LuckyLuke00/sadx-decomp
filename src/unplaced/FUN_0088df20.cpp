#include "decls.h"
extern struct ___stcFog *DAT_0480e468[];
extern struct ___stcClip *DAT_0480e450[];
extern struct ___stcClip *DAT_0480e45c[];
extern struct NJS_POINT3 *DAT_0480e444[];

// FUNCTION: SADX 0x0088df20
void FUN_0088df20(struct task *param_1)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)DAT_0480e468 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)DAT_0480e450 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)DAT_0480e45c + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)DAT_0480e444 + local_8))[DAT_05b3e0d0];
}

// FUNCTION: SADX 0x0088dfd0
void FUN_0088dfd0()
{
	ADXTaskInit();
	RoundBGM_Play(0x2a);
	ClearAllSwitches();
	TexMakeInit();
	dsPlay_iloop(0x3e7, -1, 8, 0);
}

// FUNCTION: SADX 0x0088e000
void FUN_0088e000()
{
	ADXTaskInit();
	RoundBGM_Play(0x2b);
	ClearAllSwitches();
	TexMakeInit();
	dsPlay_iloop(0x3ed, -1, 8, 0);
}
