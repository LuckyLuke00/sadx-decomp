#include "decls.h"

// GLOBAL: SADX 0x0480bd44
static struct CCL_INFO object_c_info[1];

// STUB: SADX 0x00879580
void ObjectCasinoKinkaExec(struct task *tp)
{
}

// FUNCTION: SADX 0x00879630
void ObjectCasinoKinkaInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, &object_c_info[0], 1, 4);
	}
	tp->disp = ObjectCasinoKinkaDraw;
	tp->exec = ObjectCasinoKinkaExec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var1->value.f = 400.0f;
	var1->wtimer = 0;
	var1->mode = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		var1->value.f = (var1->scl.x + 1.0) * 8.0;
	}
}

// FUNCTION: SADX 0x008796a0
void ObjectCasinoKinka(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasinoKinkaInit(tp);
	}
}
