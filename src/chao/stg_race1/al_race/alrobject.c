#include "decls.h"
extern struct task *DAT_05b35c50;

// STUB: SADX 0x0048a780
void UvScroll(union NJS_COLOR *pUv, int num, int inc_u, int inc_v)
{
}

// FUNCTION: SADX 0x0048a7f0
void AlrObjFreeManageTask()
{
	if (DAT_05b35c50)
	{
		FreeTask(DAT_05b35c50);
		DAT_05b35c50 = 0;
	}
}

// FUNCTION: SADX 0x0048a810
struct task *AlrObjSetTask(const struct TaskInfo *info_p, void *param_p)
{
	if (DAT_05b35c50 == 0)
	{
		return 0;
	}
	return MirenSetChildTask(DAT_05b35c50, info_p, param_p);
}

// STUB: SADX 0x0048a830
void AlrObjSetTaskWork(struct taskwk *taskWk_p, const struct obj *obj_p)
{
}

// STUB: SADX 0x0048a950
struct task *AlrObjSetManageTask()
{
	return (struct task *)0;
}
