#include "decls.h"
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
