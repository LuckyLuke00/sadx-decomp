#include "decls.h"
extern unsigned char DAT_05cd14ea;
struct task *FUN_00607c50(struct ModeSelPrmType *);
extern struct task *DAT_05edd9c4;

// FUNCTION: SADX 0x00607be0
struct task *SetAdvaCharSelTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, char_sel_exec);
	DAT_05edd9c4 = local_8g;
	if (DAT_05edd9c4)
	{
		local_cg = CAlloc(1, 0x38);
		local_8g->awp = (struct anywk *)local_cg;
		((void (*)(struct task *, struct ModeSelPrmType *))FUN_00607c50)(local_8g, prmp);
		local_8g->exec = char_sel_exec;
		local_8g->disp = char_sel_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x00607f80
int FUN_00607f80()
{
	return DAT_05cd14ea;
}

// FUNCTION: SADX 0x00608000
void FUN_00608000(struct AlrReal *param_1)
{
	FreeAdvaCharMdlTask();
}

// FUNCTION: SADX 0x00609560
void FreeAdvaCharSelTask()
{
	if (DAT_05edd9c4)
	{
		DestroyTask(DAT_05edd9c4);
	}
}

// FUNCTION: SADX 0x00609580
void ChgCharSelNextAdvaMode(enum AdvaModeEnum next)
{
	DAT_05edd9c4->awp->work.ul[2] = (unsigned long)next;
}
