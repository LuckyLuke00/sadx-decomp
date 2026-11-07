#include "decls.h"

// GLOBAL: SADX 0x00962f28
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_00962f40;

// FUNCTION: SADX 0x00493310
void ObjectAlrWateringCan(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00962f40);
}

// FUNCTION: SADX 0x00493330
long SendWateringcanCommand(struct task *objTask_p, struct task *chaoTask_p, signed char cmnd)
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
		case 7:
			if (*(signed char *)var1 == 2)
			{
				*(signed char *)var1 = 3;
				var2 = 1;
			}
			break;
		case 8:
			if (*(signed char *)var1 == 3)
			{
				*(signed char *)var1 = 4;
				*(struct task **)((char *)var1 + 0xc) = NULL;
				var2 = 1;
			}
			break;
		}
	}
	return var2;
}
