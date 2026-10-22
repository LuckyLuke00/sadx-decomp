#include "decls.h"
void FUN_005a0070(struct task *param_1);
extern struct task *DAT_05cda19c;

// STUB: SADX 0x0059f950
struct task *SetAdvaTitleNewTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x0059fd80
void FUN_0059fd80(struct task *param_1)
{
	if (param_1->awp)
	{
		DestroyTask((struct task *)param_1->awp);
		param_1->awp = NULL;
	}
}

// FUNCTION: SADX 0x005a0070
void FUN_005a0070(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	if (*(int *)((char *)local_8 + 0x14) == 0)
	{
		return;
	}
	if (*(int *)((char *)local_8 + 0x18) < 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)((char *)local_8 + 0x14));
	FUN_007d21b0((void *)3);
	title_new_disp((struct task *)local_8);
}

// STUB: SADX 0x005a00d0
void title_new_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005a06b0
void FreeAdvaTitleNewTask()
{
	if (DAT_05cda19c)
	{
		DestroyTask(DAT_05cda19c);
	}
}

// FUNCTION: SADX 0x005a06d0
void ChgSeqTitleNew()
{
	DAT_05cda19c->awp->work.ul[2] = 0xe;
}
