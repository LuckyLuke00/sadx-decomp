#include "decls.h"

// GLOBAL: SADX 0x03e716b8
static struct CCL_INFO object_c_info[1];

static void Normal(struct task *pTask);

// STUB: SADX 0x0081e6d0
static void Normal(struct task *pTask)
{
}

// FUNCTION: SADX 0x0081e800
void ObjectLmpa(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;

	CCL_Init(pTask, &object_c_info[0], 1, 4);
	SET_COLLI_RANGE(var1->cwp, 9.7f);
	pTask->dest = (void (*)(struct task *))FUN_007d21b0;
	pTask->exec = Normal;
	pTask->disp = Normal;
}
