#include "decls.h"
extern void *DAT_05cda188;

// FUNCTION: SADX 0x0059cdb0
void AlertWindowDestructor(struct task *tp)
{
	struct anywk *local_8;

	local_8 = tp->awp;
	if (*(int *)((char *)local_8 + 0x54) != 0)
	{
		FUN_004c3310((int *)((char *)local_8 + 0x2c));
		if (DAT_05cda188 != 0)
		{
			syFree(DAT_05cda188);
			DAT_05cda188 = 0;
		}
	}
}

// STUB: SADX 0x0059ce00
long CloseAlertWindow(struct task *tp)
{
	return (long)0;
}
