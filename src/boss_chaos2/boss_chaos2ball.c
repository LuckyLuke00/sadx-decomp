#include "decls.h"
void ___njColorBlendingMode(int tgt, int mode);
void late_DrawSprite3D(struct NJS_SPRITE *sp, int n, unsigned long atr, int flgs);
void SetMaterial(float a, float r, float g, float b);
void ResetMaterial();
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
extern struct NJS_SPRITE sprite_chaos_bshadow;
extern float DAT_05b3df40;
extern struct PL_ACTION *DAT_05edd134;
extern unsigned char DAT_060bd800;
extern struct obj object_chaos2head[1];
extern struct NJS_TEXLIST texlist_chaos2;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x006ec4c0
void Chaos2MiniBallHeadDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SaveControl3D();
		OffControl3D(0x10);
		OnControl3D(0x20);
		SaveConstantAttr();
		ResetMaterial();
		___njSetTexture(&texlist_chaos2);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (DAT_060bd800 != 0)
		{
			if (*(unsigned char *)((char *)DAT_05edd134 + 0x38) & 1)
			{
				SetMaterial(0.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		CHAOS_DrawObject((struct obj *)&object_chaos2head);
		njPopMatrix(1);
		LoadControl3D();
		LoadConstantAttr();
		___dsSetPalette(0);
	}
}

// FUNCTION: SADX 0x006ec7d0
void DisplayChaosBallShadow(struct NJS_POINT3 *pos, float size)
{
	float var1;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	var1 = size * 0.11999999731779099 * (1.0 - pos->y * 0.019999999552965164);
	if (var1 <= 0.0f)
	{
		return;
	}
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	SetMaterial(0.8f, 1.0f, 1.0f, 1.0f);
	njPushMatrix(0);
	FUN_0067d830(0, pos->x, 0.25f, pos->z);
	njRotateX(0, 0x4000);
	sprite_chaos_bshadow.sx = var1;
	sprite_chaos_bshadow.sy = var1;
	DAT_05b3df40 = -27952.0f;
	late_DrawSprite3D(&sprite_chaos_bshadow, 0, 0x20, 4);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
	ResetMaterial();
}
