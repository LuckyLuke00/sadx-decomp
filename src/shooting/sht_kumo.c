#include "decls.h"

// FUNCTION: SADX 0x007eede0
void Kumo1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.w[0] -= 1;
	if (var1->counter.w[0] != 0)
	{
		var1->pos.z -= var1->scl.z;
		KumoDisp(tp);
		if (var1->value.f < 0.0f)
		{
			var1->value.f += 0.009999999776482582;
		}
		else
		{
			var1->value.f = 0.0f;
		}
	}
	else
	{
		DestroyTask(tp);
	}
}

// FUNCTION: SADX 0x007eefe0
void sht_KUMO(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		var1->counter.f = 0.0f;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		break;
	case 1:
		CreateKumo(tp);
	}
	LoopTaskC(tp);
}
