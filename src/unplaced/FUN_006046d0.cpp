#include "decls.h"
struct task *FUN_00604760(struct task *param_1, struct ModeSelPrmType *param_2);
extern struct task *DAT_05edd9b8;

// FUNCTION: SADX 0x006046d0
void FUN_006046d0(void)
{
	if (DAT_05edd9b8)
	{
		DestroyTask(DAT_05edd9b8);
	}
}

