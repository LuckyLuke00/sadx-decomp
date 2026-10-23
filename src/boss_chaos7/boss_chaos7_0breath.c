#include "decls.h"
static void objNormalBT(struct task *tp);
extern struct obj object_c7_breath_tame_breath_tame;
extern struct NJS_TEXLIST texlist_chaos7_0breath;
extern int DAT_060c36c4;
extern int DAT_05b9d838;

// STUB: SADX 0x006fedd0
void Chaos7BreathRipple(struct task *tp)
{
}

// STUB: SADX 0x006fedf0
void Chaos7BreathParticleDisplay(struct task *tp)
{
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
