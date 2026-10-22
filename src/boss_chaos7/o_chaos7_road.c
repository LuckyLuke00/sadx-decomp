#include "decls.h"

// FUNCTION: SADX 0x00702d20
void destChaos7Road(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2;

	var2 = FUN_004c39c0(tp);
	if ((var2 == 0) && (var1->counter.ptr != 0))
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	FreeTaskC(tp);
	FreeTask(tp);
}

// FUNCTION: SADX 0x00702f20
void ObjectChaos7Road0(struct task *tp)
{
	tp->twp->btimer = 0;
	execChaos7Road(tp);
}

// FUNCTION: SADX 0x00702f40
void ObjectChaos7Road1(struct task *tp)
{
	tp->twp->btimer = 1;
	execChaos7Road(tp);
}
