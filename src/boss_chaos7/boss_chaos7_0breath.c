#include "decls.h"
extern struct NJS_ARGB DAT_02b1148c;
extern struct NJS_SPRITE sprite_breathp;
extern struct NJS_TEXANIM anim_breathp[1];
static void objNormalBT(struct task *tp);
extern struct obj object_c7_breath_tame_breath_tame;
extern struct NJS_TEXLIST texlist_chaos7_0breath;
extern int DAT_060c36c4;
extern int DAT_05b9d838;

// STUB: SADX 0x006fedd0
void Chaos7BreathRipple(struct task *tp)
{
}

// FUNCTION: SADX 0x006fedf0
void Chaos7BreathParticleDisplay(struct task *tp)
{
	struct anywk *var1 = tp->awp;
	struct taskwk *var2 = tp->twp;
	int var3 = *(int *)((char *)var2 + 0xc);

	if (DAT_05b9d838 == 0)
	{
		___njColorBlendingMode(0, 0xa);
		___njColorBlendingMode(1, 0xa);
		___njSetConstantMaterial(&DAT_02b1148c);
		--var3;
		if (var3 >= 0)
		{
			float *var4 = (float *)((char *)var1 + 0x1c);
			do
			{
				if (*var4 < 10.0f)
				{
					njPushMatrix(0);
					njTranslateV(0, (struct NJS_POINT3 *)(var4 - 7));
					anim_breathp[0].texid = (short)(long)*var4 + 9;
					late_DrawSprite3D(&sprite_breathp, 0, 0x30, 4);
					njPopMatrix(1);
				}
				var4 += 9;
				--var3;
			} while (var3 >= 0);
		}
	}
}

// STUB: SADX 0x006fee90
void Chaos7BreathParticleNormal(struct task *tp)
{
}

// FUNCTION: SADX 0x006ff130
void objDisplayBT(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njFogDisable();
		___njSetTexture(&texlist_chaos7_0breath);
		*(int *)((char *)object_c7_breath_tame_breath_tame.model->mats + 0xc) = *(short *)((char *)var1 + 0xe) + 0x23;
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
		}
		if (DAT_060c36c4 != 0)
		{
			njRotateZ((float *)0, (unsigned short)DAT_060c36c4);
		}
		FUN_0067d2d0((float *)0, 5.0f, 5.0f, 5.0f);
		late_DrawObject(&object_c7_breath_tame_breath_tame, 4);
		njPopMatrix(1);
		___njFogEnable();
	}
}

// STUB: SADX 0x006ff1f0
static void objNormalBT(struct task *tp)
{
}

// FUNCTION: SADX 0x006ff2f0
void Chaos7BreathTame(struct task *tp)
{
	tp->exec = objNormalBT;
	tp->disp = objDisplayBT;
}
