#include "decls.h"
struct task;
struct TaskInfo;
struct task *MirenSetChildTask(struct task *parent_p, const struct TaskInfo *info_p, void *param_p);

// FUNCTION: SADX 0x00570710
struct task *MirenSetTask(enum tasklevel level, const struct TaskInfo *info_p, void *param_p)
{
	struct task *local_8;

	local_8 = CreateElementalTask(*(int *)((char *)info_p + 0xc), (long)level, (void (*)(struct task *))(*(int *)((char *)info_p + 4) & 0xfffffffe));
	if (local_8 != NULL)
	{
		local_8 = MirenInitTask(local_8, info_p, param_p);
	}
	return local_8;
}

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

// FUNCTION: SADX 0x005707b0
struct task *MirenInitTask(struct task *task_p, const struct TaskInfo *info_p, void *param_p)
{
	int iVar1;
	struct task *local_10;
	int local_8g;

	iVar1 = *(int *)info_p;
	if (iVar1 > 0)
	{
		local_10 = (struct task *)MAlloc((unsigned int)iVar1);
		if (local_10 == (struct task *)0x0)
		{
			FreeTask(task_p);
			task_p = (struct task *)0x0;
		}
		else
		{
			*(void **)((char *)task_p + 0x24) = local_10;
		}
	}
	if (task_p != (struct task *)0x0)
	{
		*(void **)((char *)task_p + 0x10) = *(void **)((char *)info_p + 0xc);
		*(void **)((char *)task_p + 0x14) = *(void **)((char *)info_p + 0x10);
		*(void **)((char *)task_p + 0x18) = *(void **)((char *)info_p + 0x14);
		local_8g = *(int *)((char *)info_p + 8);
		if (local_8g != 0)
		{
			(*(void (**)(struct task *, void *))(int *)local_8g)(task_p, param_p);
		}
	}
	return task_p;
}
