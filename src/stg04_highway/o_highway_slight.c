#include "decls.h"
static void Norm(struct task *tp);

// GLOBAL: SADX 0x03e71d8c
static struct CCL_INFO object_c_info[1];

static void Draw(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00821ff0
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00822190
static void Norm(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 25000000.0f))
	{
		return;
	}
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
		ObjectSetupInput(var1, 0);
	}
	Draw(tp);
	var1->wtimer++;
}

// FUNCTION: SADX 0x008221e0
void ObjectHighwaySlight(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 25000000.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_c_info[0], 1, 4);
			SET_COLLI_RANGE(var1->cwp, 25.0f);
		}
		tp->disp = Draw;
		tp->exec = Norm;
	}
}
