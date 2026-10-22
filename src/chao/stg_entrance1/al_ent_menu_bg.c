#include "decls.h"
extern void *DAT_05b33018;

// STUB: SADX 0x004764e0
void AL_EntranceMenuBackGroundExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x00476560
void CreateBackGround(struct task *tp)
{
	if (*(struct task **)((char *)DAT_05b33018 + 0xf0) == 0)
	{
		struct task *var1;
		var1 = CreateElementalTask(2, 3, AL_EntranceMenuBackGroundExecutor);
		var1->disp = AL_EntranceMenuBackGroundDisplayer;
		var1->dest = (void (*)(struct task *))FUN_007d21b0;
		*(struct task **)((char *)DAT_05b33018 + 0xf0) = var1;
	}
}
