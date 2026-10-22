#include "decls.h"
extern struct TaskInfo DAT_00a0a678;
extern struct task *DAT_060cd388;

// FUNCTION: SADX 0x007e7150
struct task *SandObjSetChildTask(const struct TaskInfo *info_p, void *param_p)
{
	if (DAT_060cd388 == 0)
	{
		return 0;
	}
	return MirenSetChildTask(DAT_060cd388, info_p, param_p);
}

// FUNCTION: SADX 0x007e7220
struct task *SandObjSetManageTask()
{
	return MirenSetTask((enum tasklevel)3, &DAT_00a0a678, 0);
}
