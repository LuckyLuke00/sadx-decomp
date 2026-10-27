#include "decls.h"
void FUN_00853490(void);
extern struct NJS_SPRITE DAT_060d12f0;
extern int DAT_05b9d838;
extern struct NJS_TEXLIST tex_jet;

// FUNCTION: SADX 0x008533b0
void DrawFire(struct task *tp)
{
	struct NJS_ARGB argb;
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&tex_jet);
	argb.a = 1.0f;
	argb.r = 0.14f;
	argb.g = 0.11f;
	argb.b = 0.0f;
	___njSetConstantMaterial(&argb);
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	___njFogDisable();
	___njDrawSprite3D(&DAT_060d12f0, 0, 0x33);
	njPopMatrix(1);
	___njFogEnable();
	ResetMaterial();
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// FUNCTION: SADX 0x00853490
void FUN_00853490(void)
{
	DAT_060d12f0.sx = 0.35f;
	DAT_060d12f0.tlist = &tex_jet;
	DAT_060d12f0.sy = 0.35f;
	DAT_060d12f0.tanim = anim_jet;
	DAT_060d12f0.p.x = 0.0f;
	DAT_060d12f0.p.y = 0.0f;
	DAT_060d12f0.p.z = 0.0f;
}

// STUB: SADX 0x008534d0
void ObjectRuinFire(struct task *tp)
{
}
