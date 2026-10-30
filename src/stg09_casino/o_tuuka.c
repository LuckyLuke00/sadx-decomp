#include "decls.h"
static void Exit(struct task *tp);

// GLOBAL: SADX 0x0480d240
static struct CCL_INFO object_c_info[4];

static void Normal2(struct task *tp);

// FUNCTION: SADX 0x00883c50
static void Exit(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		FreeTaskC(tp);
	}
}

// STUB: SADX 0x00883da0
void cNormal1(struct task *ctp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00883fe0
static void Normal2(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008841a0
void ObjectRightLane(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 1;
	var1->btimer = 0;
	CCL_Init(tp, &object_c_info[3], 1, 4);
	tp->exec = Normal2;
	tp->dest = Exit;
}
