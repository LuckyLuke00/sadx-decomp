#include "decls.h"
extern void *DAT_060b5fec;
extern unsigned char DAT_060b5fe4;
extern unsigned char DAT_060b5fe5;
void syFree(void *param_1);

// FUNCTION: SADX 0x00691b20
void CreamManagerDestruct(struct task *tp)
{
	void *var1 = DAT_060b5fec;

	DAT_060b5fe5 = 0;
	DAT_060b5fe4 = 0;
	if (var1 != 0)
	{
		syFree(var1);
		DAT_060b5fec = 0;
	}
}

// STUB: SADX 0x00691d60
void FUN_00691d60(void *param_1)
{
}

// FUNCTION: SADX 0x006922a0
void CreateCreamManager(unsigned long idx)
{
	struct task *local_4;

	if (DAT_060b5fe5 == 0)
	{
		local_4 = CreateElementalTask(2, 4, CreamManager);
		if (local_4 != NULL)
		{
			local_4->twp->counter.l = idx;
			local_4->dest = CreamManagerDestruct;
			DAT_060b5fe5 = 1;
			DAT_060b5fe4 = 0;
		}
	}
}
