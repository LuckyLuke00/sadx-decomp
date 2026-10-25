#include "decls.h"
extern unsigned long DAT_060dd890;

// FUNCTION: SADX 0x006c13a0
void BgDisplayer(struct task *tp)
{
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	___njFogDisable();
	___njSetTexture(&texlist_egm1sora);
	njPushMatrix((float *)0);
	FUN_0067d830((float *)0, DAT_05b42a7c->pos.x, 0.0f, DAT_05b42a7c->pos.z);
	njScaleV((float *)0, &DAT_05b3e074);
	ds_DrawObjectClip((struct obj *)&object_mra_s_sora_hare_s_sora_hare, FUN_004a1e90((float *)&DAT_05b3e074));
	njPopMatrix(1);
	___njFogEnable();
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
	late_SetFunc((void (__cdecl *)(void *))DrawSaltWater3D_20, &DAT_060dd890, -7952.0f, 1);
}
