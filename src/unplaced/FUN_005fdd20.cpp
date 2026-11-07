#include "decls.h"
extern struct task *DAT_05edd9a0;

// FUNCTION: SADX 0x005fdd20
void FUN_005fdd20(void)
{
	if (DAT_05edd9a0)
	{
		DestroyTask(DAT_05edd9a0);
	}
}

// STUB: SADX 0x005fdd40
void FUN_005fdd40(unsigned long param_1, struct NJS_SPRITE *param_2, unsigned short param_3, unsigned long param_4, unsigned long param_5, float param_6, unsigned long param_7, unsigned long param_8, unsigned long param_9)
{
}

// FUNCTION: SADX 0x005fdef0
void FUN_005fdef0(unsigned long param_1, int param_2, short param_3, float param_4, float param_5, float param_6, float param_7, float param_8, int param_9)
{
	struct NJS_SPRITE local_3cg;
	struct NJS_TEXANIM local_1cg;
	float local_40;

	local_1cg.sx = 2;
	local_1cg.sy = 2;
	local_1cg.cx = 1;
	local_1cg.cy = 1;
	local_1cg.u1 = 0;
	local_1cg.v1 = 0;
	local_1cg.u2 = 0xff;
	local_1cg.v2 = 0xff;
	local_1cg.texid = param_3;
	local_1cg.attr = 0;
	local_3cg.p.x = param_4;
	local_3cg.p.y = param_5;
	local_3cg.p.z = param_6;
	local_3cg.sx = param_7;
	local_3cg.sy = param_8;
	local_3cg.ang = param_9;
	local_3cg.tlist = (struct NJS_TEXLIST *)param_2;
	local_3cg.tanim = &local_1cg;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	SaveControl3D();
	njControl3D(0x10);
	SetMaterial((float)((param_1 >> 0x18) & 0xff) / 256.0, (float)((param_1 >> 0x10) & 0xff) / 256.0, (float)((param_1 >> 8) & 0xff) / 256.0, (float)(param_1 & 0xff) / 256.0);
	local_40 = -param_6;
	if (local_40 >= -3.0 && local_40 < 12048.0)
	{
		local_40 = local_40 + 22048.0;
	}
	late_DrawSprite2D(&local_3cg, 0, local_40, 0x23, 4);
	ResetMaterial();
	LoadControl3D();
}
