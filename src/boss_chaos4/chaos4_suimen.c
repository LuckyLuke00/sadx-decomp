#include "decls.h"
void C4PondObjCreate(struct SuimenTask *st, struct task *pTask);

// STUB: SADX 0x006f0390
void C4PondObjCreate(struct SuimenTask *st, struct task *pTask)
{
}

// STUB: SADX 0x006f05f0
void FUN_006f05f0(float *param_1)
{
}

// STUB: SADX 0x006f0680
void Dsp_SuimenYurashi(struct task *pTask)
{
}

// STUB: SADX 0x006f0770
void End_SuimenYurashi(struct task *pTask)
{
}

// STUB: SADX 0x006f0830
void Dsp_first_pond(struct task *pTask)
{
}

// FUNCTION: SADX 0x006f0a20
void Exe_side_collision(struct task *pTask)
{
	if (DAT_05baf368[0]->pos.y < 0.0f)
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
