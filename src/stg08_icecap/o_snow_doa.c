#include "decls.h"

// FUNCTION: SADX 0x008660c0
void DoaExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct colliwk *var2 = var1->cwp;

	if (CheckRangeOutWithR(tp, 1690000.0f) != 0)
	{
		return;
	}
	if (FUN_004c39c0(tp) != 0)
	{
		goto end;
	}
	switch (var1->mode)
	{
	case 0:
		if (GetBigturaraStatus() != 0)
		{
			dsPlay_timer(0xdc, (int)var1, 1, 0, 0x5a);
			var1->mode = 1;
			*(int *)((char *)var2->info + 0x94) |= 0x10;
		}
		else
		{
			var2->info->angz = var1->counter.l;
		}
		break;
	case 1:
		if (var1->counter.l < 0x4000)
		{
			var1->value.l += 2;
			var1->counter.l += var1->value.l;
			var2->info->angz = var1->counter.l;
		}
		if (var1->counter.l >= 0x4000 && var1->timer.w[1] == 0)
		{
			var1->counter.l = 0x4000;
			var1->timer.w[1] = 1;
			var1->mode = 2;
			var2->info->angz = 0x4000;
		}
		*(int *)((char *)var1 + 0x1c) = -var1->counter.l;
		break;
	case 2:
		dsPlay_oneshot(0xdd, 0, 0, 0);
		var1->mode = 3;
		break;
	}
end:
	DoaDraw(tp);
	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(var1);
	}
}
