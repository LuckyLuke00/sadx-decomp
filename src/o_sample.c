#include "decls.h"
extern void ObjectSampleSWRegular(struct task *tp);

// GLOBAL: SADX 0x04c2e8f8
static struct CCL_INFO object_c_info[8];

// FUNCTION: SADX 0x008c1870
void ObjectSampleS(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	local_cg->counter.ptr = &object_cylinder01[0];
	if (FUN_004c39c0(tp) == 0)
		CCL_Init(tp, &object_c_info[0], 2, 4);
	ObjectMovableInitialize(local_cg, local_8g, 4);
	tp->dest = (void (__cdecl *)(struct task *))FUN_008be060;
	tp->exec = ObjectSampleSRegular;
}

// FUNCTION: SADX 0x008c18f0
void ObjectSampleSRegular(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	if (CheckRangeOut(tp) != 0)
		return;
	ObjectMovableSRegularExecute(tp);
	ModelTurnWhite(local_cg, 0xff);
	njPushMatrix(0);
	FUN_0067d830(0, local_cg->pos.x, local_cg->pos.y + 2.5f, local_cg->pos.z);
	if (local_cg->ang.y != 0)
		njRotateY(0, (Uint16)local_cg->ang.y);
	FUN_0067d2d0(0, 0.25f, 0.25f, 0.25f);
	___dsDrawObject((struct obj *)local_cg->counter.ptr);
	njPopMatrix(1);
	ResetMaterial();
}

// FUNCTION: SADX 0x008c19e0
void ObjectSampleM(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	local_cg->counter.ptr = &object_cylinder01[0];
	if (FUN_004c39c0(tp) == 0)
		CCL_Init(tp, &object_c_info[2], 2, 4);
	ObjectMovableInitialize(local_cg, local_8g, 5);
	tp->dest = (void (__cdecl *)(struct task *))FUN_008be060;
	tp->exec = ObjectSampleMRegular;
}

// FUNCTION: SADX 0x008c1a60
void ObjectSampleMRegular(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	if (CheckRangeOut(tp) != 0)
		return;
	ObjectMovableMRegularExecute(tp);
	ModelTurnWhite(local_cg, 0xff);
	njPushMatrix(0);
	FUN_0067d830(0, local_cg->pos.x, local_cg->pos.y + 5.0f, local_cg->pos.z);
	if (local_cg->ang.y != 0)
		njRotateY(0, (Uint16)local_cg->ang.y);
	FUN_0067d2d0(0, 0.5f, 0.5f, 0.5f);
	___dsDrawObject((struct obj *)local_cg->counter.ptr);
	njPopMatrix(1);
	ResetMaterial();
}

// FUNCTION: SADX 0x008c1b50
void ObjectSampleL(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	local_cg->counter.ptr = &object_cylinder01[0];
	if (FUN_004c39c0(tp) == 0)
		CCL_Init(tp, &object_c_info[4], 2, 4);
	ObjectMovableInitialize(local_cg, local_8g, 6);
	tp->dest = (void (*)(struct task *))FUN_008be060;
	tp->exec = ObjectSampleLRegular;
}

// FUNCTION: SADX 0x008c1bd0
void ObjectSampleLRegular(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	if (CheckRangeOut(tp) != 0)
		return;
	ObjectMovableMRegularExecute(tp);
	ModelTurnWhite(local_cg, 0x80);
	njPushMatrix(0);
	FUN_0067d830(0, local_cg->pos.x, local_cg->pos.y + 15.0f, local_cg->pos.z);
	if (local_cg->ang.y != 0)
		njRotateY(0, (Uint16)local_cg->ang.y);
	FUN_0067d2d0(0, 1.5f, 1.5f, 1.5f);
	___dsDrawObject((struct obj *)local_cg->counter.ptr);
	njPopMatrix(1);
	ResetMaterial();
}

// FUNCTION: SADX 0x008c1cc0
void ObjectSampleSW(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	local_cg->counter.ptr = &object_cylinder01[0];
	if (FUN_004c39c0(tp) == 0)
		CCL_Init(tp, &object_c_info[6], 2, 4);
	ObjectMovableInitialize(local_cg, local_8g, 7);
	tp->dest = (void (__cdecl *)(struct task *))FUN_008be060;
	tp->exec = ObjectSampleSWRegular;
}

// FUNCTION: SADX 0x008c1d40
void ObjectSampleSWRegular(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	if (CheckRangeOut(tp) != 0)
		return;
	ModelTurnWhite(local_cg, 0xff);
	njPushMatrix(0);
	FUN_0067d830(0, local_cg->pos.x + local_8g->acc.x, local_cg->pos.y + 20.0f + local_8g->acc.y, local_cg->pos.z + local_8g->acc.z);
	if (local_cg->ang.y != 0)
		njRotateY(0, (Uint16)local_cg->ang.y);
	FUN_0067d2d0(0, 0.25f, 2.0f, 0.25f);
	___dsDrawObject((struct obj *)local_cg->counter.ptr);
	njPopMatrix(1);
	ResetMaterial();
	ObjectSwingableRegularExecute(tp);
}
