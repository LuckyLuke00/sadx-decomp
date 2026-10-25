#include "decls.h"
void ObjectRuinSnakeEv(struct task *tp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x00858f00
void ObjectRuinSnakeEv(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (((int)DAT_05b9d724 << 8 | (int)DAT_05b9d744) != (int)var1->timer.w[0])
	{
		FreeTask(tp);
		return;
	}
	switch (var1->mode)
	{
		case 0:
			var1->mode = 2;
			break;
		case 2:
			var1->mode = 3;
			break;
		case 3:
			FreeTask(tp);
			break;
	}
}

// FUNCTION: SADX 0x008590d0
void EndC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->btimer == 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->value.ptr);
		ReleaseMobileLandObject((struct obj *)var1->value.ptr);
		NpcMilesSetStandByFlag(0);
	}
}
