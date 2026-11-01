#include "decls.h"

// GLOBAL: SADX 0x00962f54
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_00962f6c;

// FUNCTION: SADX 0x00493380
void ObjectAlrBugle(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00962f6c);
}

// FUNCTION: SADX 0x004933a0
long SendBugleCommand(struct task *objTask_p, struct task *chaoTask_p, signed char cmnd)
{
	struct motionwk *var1;
	long var2;
	var1 = objTask_p->mwp;
	var2 = 0;
	if (*(struct task **)((char *)var1 + 0xc) == chaoTask_p)
	{
		switch (cmnd)
		{
		case 0:
			*(struct task **)((char *)var1 + 0xc) = NULL;
			var2 = 1;
			break;
		case 9:
			if (*(signed char *)((char *)var1 + 0) == 2)
			{
				*(signed char *)((char *)var1 + 0) = 3;
				var2 = 1;
			}
			break;
		case 10:
			if (*(signed char *)((char *)var1 + 0) == 3)
			{
				*(signed char *)((char *)var1 + 0) = 4;
				*(struct task **)((char *)var1 + 0xc) = NULL;
				var2 = 1;
			}
			break;
		}
	}
	return var2;
}
