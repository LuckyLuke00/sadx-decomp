#include "decls.h"

// FUNCTION: SADX 0x007da560
void FUN_007da560(void)
{
	struct task *local_4;

	local_4 = CreateElementalTask(2, 5, 0);
	DAT_060cca6c = local_4;
	if (local_4 != NULL)
	{
		local_4->exec = frog_exec;
		local_4->disp = frog_disp;
		local_4->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		local_4->twp->ang.y = 0;
	}
}
