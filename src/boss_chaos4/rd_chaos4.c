#include "decls.h"
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT2 DAT_05b3e080;
void FUN_004a0520(float param_1, float param_2);
void ___njFogEnable();
void ___njFogDisable();
void Dsp_Air();

// FUNCTION: SADX 0x006ede20
void FUN_006ede20(struct task *param_1)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Chaos04 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Chaos04 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Chaos04 + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Chaos04 + local_8))[DAT_05b3e0d0];
}

// FUNCTION: SADX 0x006edf00
void RdChaos4_Dsp_Air(struct task *tp)
{
	___njFogDisable();
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	Dsp_Air();
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
	___njFogEnable();
}

// FUNCTION: SADX 0x006edf50
void Bg_Chaos4(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	switch (var1->mode)
	{
	case 0:
		___njSetBackColor(0x1040, 0x401074, 0x807474);
		var1->mode = 1;
		___njFogDisable();
		Dsp_Air();
		___njFogEnable();
		break;
	case 1:
		___njFogDisable();
		Dsp_Air();
		___njFogEnable();
		break;
	case 2:
		var1->mode = 0;
		break;
	default:
		Free(tp);
		break;
	}
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
}
