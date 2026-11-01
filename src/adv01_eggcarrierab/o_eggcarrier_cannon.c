#include "decls.h"

// FUNCTION: SADX 0x0069bdf0
void Term(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	void *var2 = var1->value.ptr;
	Free(var2);
	struct task *var3 = (struct task *)var1->timer.ptr;
	if (var3 != 0)
	{
		FUN_0069bd30((struct task *)var3->awp);
		FUN_0069bd30((struct task *)var3->thp);
		Free(var3);
	}
	FUN_004c39c0(tp);
}

// FUNCTION: SADX 0x0069c370
void CollisionAttackBox(struct task *tp)
{
	struct taskwk *var2 = tp->twp;
	struct taskwk *var1 = DAT_05baf368[0];
	switch (var2->mode)
	{
	case 0:
		CCL_Init(tp, &cinfo_attack[0], 1, 5);
		var2->cwp->colli_range = 40.0f;
		var2->mode = 1;
		break;
	case 1:
		dsPlay_timer(0x22d, (int)var2, 1, 0, 2);
		if ((var1->flag & 3) != 0)
		{
			FreeTask(tp);
			return;
		}
		break;
	}
	var2->pos = var1->pos;
	EntryColliList(var2);
}
