#include "decls.h"
extern struct task *DAT_05edd9b8;

// FUNCTION: SADX 0x006046d0
void FUN_006046d0(void)
{
	if (DAT_05edd9b8)
	{
		DestroyTask(DAT_05edd9b8);
	}
}

// STUB: SADX 0x006046f0
struct task *FUN_006046f0(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}
