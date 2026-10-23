#include "decls.h"
extern struct PL_JOIN_VERTEX chaos4_jv_list[1];
extern struct NJS_ACTION _action_c4_wait0_c4_kihon0_chaos4[1];
extern struct task *DAT_060cc954;

// FUNCTION: SADX 0x007d8100
void DeleteChaos4(void)
{
	if (DAT_060cc954 != NULL)
	{
		FreeTask(DAT_060cc954);
	}
}

// FUNCTION: SADX 0x007d84b0
void destChaos4Task(struct task *p_task)
{
	struct taskwk *var1;

	var1 = p_task->twp;
	ChaosJoinVertexes((struct PL_JOIN_VERTEX *)&chaos4_jv_list, (struct NJS_ACTION *)&_action_c4_wait0_c4_kihon0_chaos4, var1->counter.f, 0x5c, 2);
	if (var1->value.ptr != NULL)
	{
		Free(var1->value.ptr);
	}
}

// FUNCTION: SADX 0x007d8710
void initChaos4Task(struct task *p_task)
{
	p_task->exec = execChaos4Task;
	p_task->disp = dispChaos4Task;
	p_task->dest = destChaos4Task;
}
