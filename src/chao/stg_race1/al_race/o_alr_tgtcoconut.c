#include "decls.h"
extern NJS_POINT3 DAT_05b35c58[8];

// FUNCTION: SADX 0x004900e0
long SendTargetCoconutCommand(struct task *objTask_p, struct task *chaoTask_p, signed char cmnd)
{
	struct motionwk *var1;
	long var2;
	var1 = objTask_p->mwp;
	var2 = 0;
	if (*(struct task **)((char *)var1 + 0x18) == chaoTask_p)
	{
		switch (cmnd)
		{
		case 0:
			*(struct task **)((char *)var1 + 0x18) = NULL;
			var2 = 1;
			break;
		case 3:
			if (*(signed char *)((char *)var1 + 0) == 2)
			{
				*(short *)((char *)var1 + 0x2) = 0;
				*(signed char *)((char *)var1 + 0) = 3;
				var2 = 1;
			}
			break;
		case 4:
			if (*(signed char *)((char *)var1 + 0) == 3)
			{
				*(struct task **)((char *)var1 + 0x18) = NULL;
				FreeTask(objTask_p);
				var2 = 1;
			}
			break;
		}
	}
	return var2;
}

// FUNCTION: SADX 0x00490140
long GetTargetCoconutPosition(struct NJS_POINT3 *pos_p, int chaoId)
{
	if (pos_p && (unsigned int)chaoId <= 7)
	{
		*pos_p = DAT_05b35c58[chaoId];
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00490310
void destObject(struct task *task_p)
{
	AlrCommuSendChaoCommand((struct task *)*(int **)((char *)task_p->mwp + 0x18), task_p, 0, 1);
}

// STUB: SADX 0x00490330
float FUN_00490330(struct task *tp)
{
	return (float)0;
}

// STUB: SADX 0x00490490
struct task *SetTargetCoconut(int id, const struct NJS_POINT3 *pos_p, const struct Angle3 *ang_p, struct task *chaoTask_p)
{
	return (struct task *)0;
}
