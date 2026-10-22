#include "decls.h"

// FUNCTION: SADX 0x006f0a20
void Exe_side_collision(struct task *pTask)
{
	if (*(float *)((char *)DAT_05baf368 + 0x24) < 0.0f)
	{
		ADX_Close();
		KillHimByFallingDownP(0);
	}
}

// FUNCTION: SADX 0x006f0a50
void End_side_collision(struct task *pTask)
{
	ReleaseMobileLandObject((struct obj *)pTask->awp);
	pTask->awp = NULL;
}

// STUB: SADX 0x006f0be0
void Chaos4SuimenChange(long inorder)
{
}

// FUNCTION: SADX 0x006f0c20
void Chaos4SideCollisionSet()
{
	struct task *local_8;
	struct obj *local_4;

	local_8 = CreateElementalTask(6, 3, Exe_side_collision);
	if (local_8 != 0)
	{
		EnemyInitialize(local_8, local_8->twp);
		local_4 = GetMobileLandObject();
		*(struct obj *)local_4 = object_c4_ar_s_kabeb_ar_s_kabeb[0];
		local_4->evalflags &= 0xfffffffc;
		local_8->awp = (struct anywk *)local_4;
		local_8->twp->flag |= 0x100;
		RegisterCollisionEntry(0x20200001, local_8, local_4);
		local_8->exec = Exe_side_collision;
		local_8->dest = End_side_collision;
	}
}
