#include "decls.h"

// FUNCTION: SADX 0x006f44f0
void DisplaySky(struct taskwk *twp)
{
	if (DAT_05b9d838)
	{
		return;
	}
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	SaveControl3D();
	OffControl3D(0x40);
	___njFogDisable();
	___njSetTexture(&texlist_chaos6_bg);
	njPushMatrix(0);
	FUN_0067d830(0, DAT_05b42a7c->pos.x, 0.0f, DAT_05b42a7c->pos.z);
	njRotateY(0, 0xe000);
	njScaleV(0, &DAT_05b3e074);
	___dsDrawObject((struct obj *)&object_ecsc_s_sora_s_sora);
	njPopMatrix(1);
	___njFogEnable();
	LoadControl3D();
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
}
