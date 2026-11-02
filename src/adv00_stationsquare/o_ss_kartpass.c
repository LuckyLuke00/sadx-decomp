#include "decls.h"
static void exitSSCard(struct task *tp);
static long SeqCheck();

// GLOBAL: SADX 0x026dd038
static struct CCL_INFO obj_c_info[2];

static void Exec(struct task *tp);
static void disp(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00687ac0
static long SeqCheck()
{
	return (long)0;
}
#pragma optimize("", on)

// STUB: SADX 0x00687ba0
static void disp(struct task *tp)
{
}

// FUNCTION: SADX 0x00687c80
static void exitSSCard(struct task *tp)
{
	tp->ocp->ssCondition &= 0xbfff;
}

// STUB: SADX 0x00687ca0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00688220
void ObjectSSKartpass(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;

	var1->scl.x = 1.0f;
	var1->scl.y = 1.0f;
	var1->value.f = 0.0f;
	var1->btimer = 0;
	var1->wtimer = 0;
	var1->mode = (GetHoldingItemIDP(0) != 4) - 1 & 3;
	ObjectMovableInitialize(var1, var2, 4);
	var1->flag |= 2;
	tp->exec = Exec;
	tp->dest = exitSSCard;
	tp->disp = disp;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, &obj_c_info[0], 2, 4);
		if (SeqCheck() == 0)
		{
			var1->mode = 6;
			tp->disp = NULL;
		}
	}
}
