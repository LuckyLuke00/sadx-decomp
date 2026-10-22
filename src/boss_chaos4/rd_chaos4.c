#include "decls.h"
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT2 DAT_05b3e080;
void FUN_004a0520(float param_1, float param_2);
void ___njFogEnable();
void ___njFogDisable();
void Dsp_Air();

// FUNCTION: SADX 0x006edf00
void RdChaos4_Dsp_Air(struct task *tp)
{
	___njFogDisable();
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	Dsp_Air();
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
	___njFogEnable();
}
