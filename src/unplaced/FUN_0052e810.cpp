#include "decls.h"
extern int DAT_06274af0;
extern void *DAT_06298ca8;

// FUNCTION: SADX 0x0052e810
void FUN_0052e810(struct task *param_1)
{
	struct motionwk *local_8;

	local_8 = (struct motionwk *)CAlloc(1, 0x20);
	if (local_8 == 0)
	{
		return;
	}
	param_1->mwp = local_8;
	*(long *)((char *)local_8 + 0x10) = *(long *)((char *)DAT_06274af0 + 0xd8);
	*(long *)((char *)local_8 + 0x14) = *(long *)((char *)DAT_06274af0 + 0xdc);
	*(long *)((char *)local_8 + 0x18) = *(long *)((char *)DAT_06274af0 + 0xe0);
	*(long *)((char *)local_8 + 0x1c) = *(long *)DAT_06298ca8;
	param_1->dest = PlayerFaceMotionEnd;
	param_1->exec = PlayerFaceMotionExec;
}
