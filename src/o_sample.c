#include "decls.h"
struct taskwk *local_8;
struct motionwk *local_4;

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
