#include "decls.h"
extern long vertex_al_hrp_reg_l[153];
extern void *DAT_060eea60;
struct NJS_TEXLIST;
int FUN_006fccc0(struct taskwk *param_1);
void FUN_006fd310(struct task *param_1);
extern unsigned char DAT_060c35f0;

// FUNCTION: SADX 0x006fbae0
void EffectAuraDestruct(struct task *tp)
{
	dsStop_num(0x41f);
	dsStop_num(0x420);
}

// STUB: SADX 0x006fcad0
void EffectSSSpinDSExecute(struct task *tp)
{
}

// STUB: SADX 0x006fcb30
void EffectSSStartHomingDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_ARGB argb;
	SaveConstantAttr();
	OnConstantAttr(0, (unsigned long)&vertex_al_hrp_reg_l[112]);
	argb.b = 0.0;
	argb.g = 0.0;
	argb.r = 0.0;
	argb.a = ((float)var1->wtimer * -1.0) / 10.0;
	___njSetConstantMaterial(&argb);
	___njSetTexture((struct NJS_TEXLIST *)(void *)(*(int *)&var1->value));
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	FUN_0067d2d0(0, *(float *)&var1->scl, *(float *)&var1->scl, *(float *)&var1->scl);
	late_DrawObject(*(struct obj **)((char *)DAT_060eea60 + 0xe0), 4);
	njPopMatrix(1);
	ResetMaterial();
	LoadConstantAttr();
}

// STUB: SADX 0x006fcc10
void EffectSSStartHomingExecute(struct task *tp)
{
}

// STUB: SADX 0x006fce50
void EffectSSDashDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x006fd350
void EffectSuperSonicAura(struct task *tp)
{
	tp->exec = EffectAuraExecute;
	tp->disp = EffectAuraDisplay;
	tp->dest = EffectAuraDestruct;
	EffectAuraDisplay(tp);
	DAT_060c35f0 = 0;
}

// FUNCTION: SADX 0x006fd3e0
void EffectSSDash(struct task *tp)
{
	if (FUN_006fccc0(tp->twp) == 1)
	{
		tp->exec = EffectSSDashExecute;
		tp->disp = EffectSSDashDisplay;
		tp->dest = FUN_006fd310;
	}
	else
	{
		FreeTask(tp);
	}
}
