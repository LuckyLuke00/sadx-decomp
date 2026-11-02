#include "decls.h"

// GLOBAL: SADX 0x026dd880
static struct CCL_INFO object_c_info[1];

static void Exec(struct task *tp);
static void Disp(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00689b90
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00689de0
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
	{
		float var2 = var1->counter.f + 0.004999999888241291;
		if (var2 >= 1.0)
		{
			var2 = var2 - 1.0;
		}
		var1->counter.f = var2;
		Disp(tp);
	}
}

// FUNCTION: SADX 0x00689e50
void ObjectSSWakusei(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;
	var1->counter.f = 0.0f;
	var1->ang.x = 0;
	var1->ang.y = 0;
	var1->ang.z = 0;
	var1->mode = 0;
	var2->ang_aim.x = 0;
	var2->ang_aim.y = 0;
	var2->ang_aim.z = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
	}
	tp->exec = Exec;
	tp->disp = Disp;
}
