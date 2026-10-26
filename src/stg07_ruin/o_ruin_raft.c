#include "decls.h"
extern "C" double floor(double param_1);
extern "C" double floor(double param_1);
extern int DAT_060d1344;

// FUNCTION: SADX 0x00857320
void End(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
	ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	FreeTaskC(tp);
	DAT_060d1344 = 0;
}

// FUNCTION: SADX 0x00857470
void EruptFire(struct sp_task *tp, struct sp_link *lp)
{
	short var1;

	tp->no = (short)floor(tp->frame);
	var1 = (short)lp->info->animnum;
	if (tp->no >= var1)
	{
		tp->no = var1 - 1;
		SpFreeTask(tp);
		return;
	}
	tp->frame = tp->frame + 0.33f;
	tp->spd.x = tp->spd.x - tp->spd.x * 0.05f;
	tp->spd.y = tp->spd.y + (0.02f - tp->spd.y * 0.05f);
	tp->spd.z = tp->spd.z - tp->spd.z * 0.05f;
	tp->pos.x = tp->pos.x + tp->spd.x;
	tp->pos.y = tp->pos.y + tp->spd.y;
	tp->pos.z = tp->pos.z + tp->spd.z;
	tp->scl = tp->scl + 0.0005f;
}
