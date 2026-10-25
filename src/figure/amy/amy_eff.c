#include "decls.h"
extern void AmyEffectFallHeart(struct task *tp);
extern struct NJS_TEXLIST texlist_amy_eff;
extern struct obj *DAT_060eea50;
extern struct taskwk *DAT_05baf368[8];
extern struct NJS_SPRITE sprite_amy_piyo;
extern int DAT_05b9d838;
void FreeTask(struct task *tp);

// STUB: SADX 0x005d5f50
void AmyEffectPutFallHeart(struct NJS_POINT3 *pos, long angx, long angz)
{
}

// FUNCTION: SADX 0x005d60d0
void AmyEffectFallHeartDisplayer(struct task *tp)
{
	struct taskwk *local_8g;

	local_8g = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_amy_eff);
		SetMaterial(1.0f - local_8g->counter.f, 1.0f, 1.0f, 1.0f);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 10);
		njPushMatrix(0);
		njTranslateV(0, &local_8g->pos);
		if (*(long *)((char *)local_8g + 0x18) != 0)
		{
			njRotateY(0, *(unsigned short *)((char *)local_8g + 0x18));
		}
		if (*(long *)((char *)local_8g + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)local_8g + 0x1c));
		}
		late_DrawSprite3D(&sprite_amy_heart, 0, 0x22, 4);
		njPopMatrix(1);
		ResetMaterial();
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
	}
}

// STUB: SADX 0x005d61d0
void AmyEffectFallHeart(struct task *tp)
{
}

// STUB: SADX 0x005d62d0
void AmyEffectPutSpdDwnHeart(struct NJS_POINT3 *pos)
{
}

// FUNCTION: SADX 0x005d6410
void AmyEffectSpdDwnHeartDisplayer(struct task *tp)
{
	struct taskwk *local_8g;
	float local_cg;

	local_8g = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_amy_eff);
		local_cg = local_8g->counter.f - 0.5;
		local_cg = 2.0 * (0.25 - local_cg * local_cg);
		SetMaterial(local_cg, 1.0f, 1.0f, 1.0f);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 10);
		njPushMatrix(0);
		njTranslateV(0, &local_8g->pos);
		late_DrawSprite3D(&sprite_amy_heart, 0, 0x32, 4);
		njPopMatrix(1);
		ResetMaterial();
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
	}
}

// STUB: SADX 0x005d64f0
void AmyEffectSpdDwnHeart(struct task *tp)
{
}

// FUNCTION: SADX 0x005d65c0
void AmyEffectPiyoPiyo(struct task *tp)
{
	struct taskwk *local_8g;
	float local_cg;

	local_8g = tp->twp;
	if (DAT_05baf368[0] == 0)
	{
		FreeTask(tp);
	}
	else
	{
		tp->disp = AmyEffectPiyoPiyoDraw;
		if (Amy_Status(0) != 9)
		{
			*(float *)((char *)local_8g + 0x2c) = 0.2f;
			AmyEffectPiyoPiyoEnd(tp);
			tp->exec = AmyEffectPiyoPiyoEnd;
		}
		else
		{
			*(long *)((char *)local_8g + 0x18) += 0x200;
			local_cg = 1.0f + njSin(*(long *)((char *)local_8g + 0x18) << 2) * 0.30000001192092896;
			sprite_amy_piyo.sx = local_cg;
			sprite_amy_piyo.sy = local_cg;
			AmyEffectPiyoPiyoDraw(tp);
		}
	}
}

// FUNCTION: SADX 0x005d6890
void AmyEffectPiyoPiyoEnd(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (DAT_05baf368[0] == 0)
	{
		FreeTask(tp);
		return;
	}
	local_8->scl.x -= 0.025f;
	sprite_amy_piyo.sx += local_8->scl.x;
	sprite_amy_piyo.sy += local_8->scl.x;
	if (sprite_amy_piyo.sy < 0.1f)
	{
		FreeTask(tp);
	}
	else
	{
		AmyEffectPiyoPiyoDraw(tp);
	}
}

// STUB: SADX 0x005d6920
void AmyEffectHammerWave(struct task *tp)
{
}

// STUB: SADX 0x005d6af0
void AmyEffectHammerWaveDisplayer(struct task *tp)
{
}

// STUB: SADX 0x005d6c10
void AmyEffectHammerWaveColor(struct task *tp)
{
}

// FUNCTION: SADX 0x005d6cf0
void AmyEffectHammerWaveColorDisplayer(struct task *tp)
{
	struct taskwk *local_8g;
	struct obj *local_cg;
	local_8g = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_amy_eff);
		ResetMaterial();
		njPushMatrix(0);
		njTranslateV(0, &local_8g->pos);
		if (*(int *)((char *)local_8g + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)local_8g + 0x1c));
		}
		if (local_8g->ang.x != 0)
		{
			njRotateX(0, local_8g->ang.x);
		}
		njScaleV(0, &local_8g->scl);
		local_cg = *(struct obj **)((char *)DAT_060eea50 + 0x74);
		late_DrawObject(local_cg, 4);
		njPopMatrix(1);
	}
}
