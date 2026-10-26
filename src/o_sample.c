#include "decls.h"

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
		njRotateY(0, local_cg->ang.y);
	FUN_0067d2d0(0, 0.25f, 0.25f, 0.25f);
	___dsDrawObject((struct obj *)local_cg->counter.ptr);
	njPopMatrix(1);
	ResetMaterial();
}

// STUB: SADX 0x008c1a60
void ObjectSampleMRegular(struct task *tp)
{
}

// STUB: SADX 0x008c1bd0
void ObjectSampleLRegular(struct task *tp)
{
}
