#include "decls.h"
void FUN_0055f9e0(struct task *param_1);
int FUN_0055f9f0(struct task *param_1, struct task **param_2);
extern struct task *DAT_05ccdac8;
extern struct task *DAT_05ccdacc;
void FUN_0055f9e0(struct task *param_1);

// FUNCTION: SADX 0x0055f530
struct task *InputHookInit()
{
	struct task *local_8;
	local_8 = CreateElementalTask(0, 0, inputhook_exec);
	DAT_05ccdac8 = 0;
	DAT_05ccdacc = 0;
	if (local_8 != 0)
	{
		local_8->dest = FUN_0055f9e0;
	}
	return local_8;
}

// STUB: SADX 0x0055f630
void InputHookRelease(void)
{
}

// STUB: SADX 0x0055f670
void InputHookDelete(struct task *del_task_p)
{
}

// STUB: SADX 0x0055f990
void FUN_0055f990(struct task *task)
{
}

// FUNCTION: SADX 0x0055f9e0
void FUN_0055f9e0(struct task *param_1)
{
	((void (*)())inputhook_end)();
}

// STUB: SADX 0x0055f9f0
int FUN_0055f9f0(struct task *param_1, struct task **param_2)
{
	return (int)0;
}

// STUB: SADX 0x0055fa50
void inputhook_end(struct task *task_p)
{
}
