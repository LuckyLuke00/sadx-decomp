#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// GLOBAL: SADX 0x04ad7728
static struct CCL_INFO c_info_a[2];


#pragma optimize("", off)
// STUB: SADX 0x008a5db0
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008a5e60
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(var1);
	}
	Disp(tp);
}

// FUNCTION: SADX 0x008a5e90
void ObjShelterGateside(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, c_info_a, 2, 4);
		SET_COLLI_RANGE(var1->cwp, 70.0f);
	}
	tp->exec = Exec;
	tp->disp = Disp;
}
