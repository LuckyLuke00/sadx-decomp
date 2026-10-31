#include "decls.h"
static void dispSSCard(struct task *tp);
static void exitSSCard(struct task *tp);
static long SeqCheck();
static void Exec(struct task *tp);
extern unsigned char DAT_060b5fdc;

#pragma optimize("", off)
// STUB: SADX 0x006882b0
static long SeqCheck()
{
	return (long)0;
}
#pragma optimize("", on)

// STUB: SADX 0x00688370
static void dispSSCard(struct task *tp)
{
}

// FUNCTION: SADX 0x00688450
static void exitSSCard(struct task *tp)
{
	tp->ocp->ssCondition &= 0xbfff;
	DAT_060b5fdc = 0;
}

// STUB: SADX 0x00688470
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00688570
void ObjectSSKeyice(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;

	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->wtimer = 0;
	if (!FUN_004c39c0(tp) && SeqCheck() == 0)
	{
		return;
	}
	if (DAT_060b5fdc != 0 && tp->ocp != 0)
	{
		FreeTask(tp);
		return;
	}
	DAT_060b5fdc = 1;
	var1->mode = GetHoldingItemIDP(0) == 1 ? 3 : 0;
	var1->counter.l = (long)&action_ssobj_keyice;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, cci_sscard, 2, 4);
	}
	ObjectMovableInitialize(var1, var2, 4);
	var1->flag |= 2;
	tp->exec = Exec;
	tp->dest = exitSSCard;
	tp->disp = dispSSCard;
}
