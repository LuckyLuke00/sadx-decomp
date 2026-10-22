#include "decls.h"
extern struct task *DAT_060cce58;
extern struct task *DAT_060b9954;
void FreeTask(struct task *tp);

// FUNCTION: SADX 0x006c2720
void FreeEgm1JetTask()
{
	FreeTask(DAT_060b9954);
}

// FUNCTION: SADX 0x006c2730
void ChgEgm1Jet(enum Egm1JetCmdEnum jet_cmd)
{
	struct anywk *local_8 = DAT_060b9954->awp;
	if (*(int *)((char *)local_8 + 0xa8) != 0)
	{
		*(int *)((char *)local_8 + 0xa4) = 0;
		*(int *)((char *)local_8 + 0xa8) = (int)jet_cmd;
	}
}

// FUNCTION: SADX 0x006c2760
unsigned long GetEgm1JetPassFrame()
{
	struct anywk *var1 = DAT_060b9954->awp;
	return *(unsigned long *)((char *)var1 + 0xa4);
}

// FUNCTION: SADX 0x007e0020
void evFreeEgm1JetTask(void)
{
	if (DAT_060cce58 != NULL)
	{
		DestroyTask(DAT_060cce58);
	}
}

// FUNCTION: SADX 0x007e0040
void evChgEgm1Jet(enum Egm1JetCmdEnum jet_cmd)
{
	struct anywk *var1;

	var1 = DAT_060cce58->awp;
	*(int *)((char *)var1 + 0xa4) = 0;
	*(int *)((char *)var1 + 0xa8) = jet_cmd;
}
