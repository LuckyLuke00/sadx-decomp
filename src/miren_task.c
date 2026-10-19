#include "decls.h"
struct task;
struct TaskInfo;
struct task *MirenSetChildTask(struct task *parent_p, const struct TaskInfo *info_p, void *param_p);

// FUNCTION: SADX 0x00570760
struct task *MirenSetChildTask(struct task *parent_p, const struct TaskInfo *info_p, void *param_p)
{
	struct task *local_8;
	local_8 = CreateChildTask(*(int *)((char *)info_p + 4) & 0xfffffffe, *(void (**)(struct task *))((char *)info_p + 0xc), parent_p);
	if (local_8 != (struct task *)0x0)
	{
		local_8 = MirenInitTask(local_8, info_p, param_p);
	}
	return local_8;
}
