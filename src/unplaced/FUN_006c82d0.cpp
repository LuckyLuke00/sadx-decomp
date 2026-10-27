#include "decls.h"
extern struct taskwk *DAT_05baf368[8];
extern struct CCL_INFO DAT_027dbb84[1];
extern struct taskwk *DAT_060b9b10;

// FUNCTION: SADX 0x006c82d0
void FUN_006c82d0(void)
{
	struct task *local_4;
	struct taskwk *local_8;

	local_4 = CreateElementalTask(2, 3, (void (__cdecl *)(struct task *))FUN_006877a0);
	if (local_4 != NULL)
	{
		local_8 = local_4->twp;
		EnemyInitialize(local_4, local_8);
		local_8->pos = DAT_05baf368[0]->pos;
		local_4->exec = (void (__cdecl *)(struct task *))FUN_006877a0;
		CCL_Init(local_4, (struct CCL_INFO *)&DAT_027dbb84, 1, 5);
		DAT_060b9b10 = (struct taskwk *)&local_8->pos;
	}
}
