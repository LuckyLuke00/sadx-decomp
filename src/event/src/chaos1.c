#include "decls.h"
extern struct PL_JOIN_VERTEX chaos1_jv_list[1];
extern struct NJS_ACTION action_c1_kihon0_chaos1[1];
extern struct task *DAT_060ccb48;

// FUNCTION: SADX 0x007dc050
void ToHumanChaos1()
{
	struct taskwk *var1 = DAT_060ccb48->twp;
	var1->timer.l = 0;
	var1->mode = 2;
}

// FUNCTION: SADX 0x007dc3b0
void destChaos1Task(struct task *p_task)
{
	struct taskwk *var1;

	var1 = p_task->twp;
	ChaosJoinVertexes(chaos1_jv_list, action_c1_kihon0_chaos1, var1->counter.f, 0x5c, 2);
	if (var1->value.ptr != NULL)
	{
		Free(var1->value.ptr);
	}
}

// FUNCTION: SADX 0x007dc5c0
void initChaos1Task(struct task *p_task)
{
	p_task->exec = execChaos1Task;
	p_task->disp = dispChaos1Task;
	p_task->dest = destChaos1Task;
}

// STUB: SADX 0x007dc5e0
void CreateChaos1(float pos_x, float pos_y, float pos_z, long ang_x, long ang_y, long ang_z, int cng_int)
{
}
