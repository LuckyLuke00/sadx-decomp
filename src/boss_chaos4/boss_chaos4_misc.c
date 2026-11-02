#include "decls.h"
void Chaos4HeadMode(struct taskwk *twp);
extern "C" double atan2(double v, double u);
extern struct NJS_TEXLIST texlist_chaos4_shibuki;
extern struct NJS_TEXANIM anim_chaos4_shibuki[1];
extern void Tmit_SpriteSetBase(struct NJS_SPRITE *sprite, unsigned char frame, struct NJS_POINT3 *pos, struct NJS_POINT3 *speed, float delay);
extern void Dsp_tmit_sprite(struct task *pTask);
extern void initSpriteSub(struct NJS_SPRITE *sp, const struct NJS_TEXLIST *list, const struct NJS_TEXANIM *anim);
extern struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
extern struct NJS_SPRITE DAT_060c20ec;
extern struct NJS_SPRITE DAT_060c210c;

// FUNCTION: SADX 0x006eebb0
void Chaos4HeadMode(struct taskwk *twp)
{
	struct taskwk *var1;
	int var2;
	switch (*(unsigned char *)((char *)twp->value.ptr + 0x27))
	{
	case 1:
		var1 = (struct taskwk *)twp->value.ptr;
		var2 = (int)var1->value.ptr;
		break;
	case 2:
		var1 = DAT_05baf368[0];
		var2 = (int)((double)atan2(*(float *)((char *)var1 + 0x28) - *(float *)((char *)twp + 0x28), *(float *)((char *)var1 + 0x20) - *(float *)((char *)twp + 0x20)) * 65536.0 / 6.283184);
		break;
	default:
		return;
	}
	*(int *)((char *)twp + 0x18) = (int)((double)SubAngle(*(int *)((char *)twp + 0x18), var2) * 0.30000001192092896 + (double)*(int *)((char *)twp + 0x18));
}

// FUNCTION: SADX 0x006eec20
void Tmit_MaterialInit()
{
	ResetMaterial();
}

// STUB: SADX 0x006eec30
void Chaos4EmeraldSet()
{
}

// FUNCTION: SADX 0x006eec60
void Chaos4EffectInit()
{
	initSpriteSub(&DAT_060c20ec, &texlist_chaos4_shibuki, (const struct NJS_TEXANIM *)&anim_chaos4_shibuki);
	initSpriteSub(&DAT_060c210c, &texlist_chaos_effect, (const struct NJS_TEXANIM *)&anim_drop_chaos4);
}

// STUB: SADX 0x006eeda0
void Chaos4TikalSet(int cflg)
{
}

// STUB: SADX 0x006eee50
void Tmit_SpriteSetBase(struct NJS_SPRITE *sprite, unsigned char frame, struct NJS_POINT3 *pos, struct NJS_POINT3 *speed, float delay)
{
}

// FUNCTION: SADX 0x006eeef0
void Chaos4Splash_A_Set(struct NJS_POINT3 *pos)
{
	initSpriteSub(&DAT_060c20ec, &texlist_chaos4_shibuki, (const struct NJS_TEXANIM *)&anim_chaos4_shibuki);
	struct task *var1 = CreateElementalTask(2, 5, (void (__cdecl *)(struct task *))Tmit_SpriteSetBase);
	if (var1 != 0)
	{
		struct taskwk *var2 = var1->twp;
		var2->value.f = 0.5f;
		*(int *)((char *)var2 + 0x1c) = 0;
		*(int *)((char *)var2 + 0x18) = 0;
		*(float *)((char *)var2 + 8) = 0.0f;
		*(int *)((char *)var2 + 0x14) = 0;
		*(int *)((char *)var2 + 0xc) = (int)&DAT_060c20ec;
		var2->smode = 8;
		var2->pos.x = pos->x;
		var2->pos.y = pos->y;
		var2->pos.z = pos->z;
		var1->exec = (void (__cdecl *)(struct task *))Tmit_SpriteSetBase;
		var1->disp = Dsp_tmit_sprite;
	}
}
