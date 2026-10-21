#include "decls.h"
void FUN_005b47c0(struct taskwk *param_1);
void FUN_0049e8b0(struct task *param_1);

// FUNCTION: SADX 0x005b44c0
void EffectCrash(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	CrashInit(local_8);
	CrashStarGenerate(local_8);
	FUN_0049e8b0(tp);
}

// STUB: SADX 0x005b4730
void CrashStar(struct task *tp)
{
}

// FUNCTION: SADX 0x005b47a0
void CrashStarDisplayer(struct task *tp)
{
	CrashStarDraw(tp->twp);
}

// FUNCTION: SADX 0x005b47c0
void FUN_005b47c0(struct taskwk *param_1)
{
	param_1->mode = 1;
}
