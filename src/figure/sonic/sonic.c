#include "decls.h"

// FUNCTION: SADX 0x0054eab0
void FUN_0054eab0(struct taskwk *param_1)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 6, EffectSSDash);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)param_1 + 8);
	}
}

// FUNCTION: SADX 0x0054fc20
long IsSonicWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x4a)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x0054fc80
void _sonicmot_init()
{
	DAT_05cc7fe8 = *(int *)((char *)DAT_060eea5c + 0x190);
	DAT_05cc7ff8 = *(int *)((char *)DAT_060eea5c + 0x194);
}
