#include "decls.h"
extern struct PL_JOIN_VERTEX chaos2_jv_list[1];
extern struct NJS_ACTION action_c2_wait0[1];

// FUNCTION: SADX 0x007dbc00
void destChaos2Task(struct task *p_task)
{
	struct taskwk *var1;

	var1 = p_task->twp;
	ChaosJoinVertexes(chaos2_jv_list, action_c2_wait0, *(float *)((char *)var1->value.ptr + 0x24), 0x5c, 2);
	if (var1->value.ptr != NULL)
	{
		Free(var1->value.ptr);
	}
}

// FUNCTION: SADX 0x007dbe60
void initChaos2Task(struct task *p_task)
{
	p_task->exec = execChaos2Task;
	p_task->disp = dispChaos2Task;
	p_task->dest = destChaos2Task;
}
