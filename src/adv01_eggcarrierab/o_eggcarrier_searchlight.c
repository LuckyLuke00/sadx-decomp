#include "decls.h"

// STUB: SADX 0x0069ce00
void HeadExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0069d160
void ExecD(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	Draw(tp);
	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(var1);
		LoopTaskC(tp);
	}
}

// FUNCTION: SADX 0x0069d190
void HeadInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, object_c_info_head, 1, 4);
	}
	var1->scl.x = 0.0f;
	var1->ang.x = 0;
	var1->scl.y = 0.0f;
	var1->ang.y = 0;
	var1->scl.z = 0.0f;
	var1->ang.z = 0;
	tp->exec = HeadExec;
}
