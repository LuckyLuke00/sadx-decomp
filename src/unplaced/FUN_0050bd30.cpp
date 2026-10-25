#include "decls.h"
extern void *DAT_060eea78;
extern void *DAT_06298ca0;

// FUNCTION: SADX 0x0050bd30
void FUN_0050bd30(struct task *param_1)
{
	struct motionwk *local_8;

	local_8 = (struct motionwk *)CAlloc(1, 0x20);
	if (local_8 == 0)
	{
		return;
	}
	param_1->mwp = local_8;
	*(long *)((char *)local_8 + 0x10) = *(long *)((char *)DAT_060eea78 + 0x68);
	*(long *)((char *)local_8 + 0x14) = *(long *)((char *)DAT_060eea78 + 0x6c);
	*(long *)((char *)local_8 + 0x18) = *(long *)((char *)DAT_060eea78 + 0x70);
	*(long *)((char *)local_8 + 0x1c) = *(long *)DAT_06298ca0;
	param_1->dest = PlayerFaceMotionEnd;
	param_1->exec = PlayerFaceMotionExec;
}
