#include "decls.h"
extern struct NJS_TEXLIST texlist_chaos4_shibuki;
extern struct NJS_TEXANIM anim_chaos4_shibuki[1];
extern void Tmit_SpriteSetBase(struct NJS_SPRITE *sprite, unsigned char frame, struct NJS_POINT3 *pos, struct NJS_POINT3 *speed, float delay);
extern void Dsp_tmit_sprite(struct task *pTask);
extern void initSpriteSub(struct NJS_SPRITE *sp, const struct NJS_TEXLIST *list, const struct NJS_TEXANIM *anim);
extern struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
extern struct NJS_SPRITE DAT_060c20ec;
extern struct NJS_SPRITE DAT_060c210c;

// STUB: SADX 0x006eebb0
void Chaos4HeadMode(struct taskwk *twp)
{
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
