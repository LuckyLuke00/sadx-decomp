#include "decls.h"
extern struct obj object_sky_cl_obj_maruyoko_obj_maruyoko[];
extern struct obj object_sky_cl_obj_maruyoko_obj_maruyoko[1];
extern int DAT_05cbef64;

// FUNCTION: SADX 0x00848060
void ObjectSkydeck_c_talap1_End(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}

	if (var1->value.ptr != 0)
	{
		Free(var1->value.ptr);
	}
}

// FUNCTION: SADX 0x008481e0
void ObjectSkydeck_c_talap1_Exec(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		if (DAT_05cbef64 & 1)
		{
			ObjectSkydeck_c_talap1_Draw(tp);
			FUN_004c39c0(tp);
		}
	}
}

// FUNCTION: SADX 0x00848220
void ObjectSkydeck_c_talap1_Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2;

	if (FUN_004c39c0(tp) == 0)
	{
		var2 = GetMobileLandObject();
		var1->counter.ptr = var2;
		var2->scl[0] = 1.0f;
		var2->scl[1] = 1.0f;
		var2->scl[2] = 1.0f;
		var2->evalflags = 0;
		var2->ang[0] = 0;
		var2->ang[1] = var1->ang.y;
		var2->ang[2] = 0;
		var2->pos[0] = var1->pos.x;
		var2->pos[1] = var1->pos.y;
		var2->pos[2] = var1->pos.z;
		var2->model = object_sky_cl_obj_maruyoko_obj_maruyoko[0].model;
		var2->child = object_sky_cl_obj_maruyoko_obj_maruyoko[0].child;
		var2->sibling = 0;
		var1->flag |= 0x100;
		RegisterCollisionEntry(0x40000001, tp, var2);
	}
	tp->disp = ObjectSkydeck_c_talap1_Draw;
	tp->exec = ObjectSkydeck_c_talap1_Exec;
	tp->dest = ObjectSkydeck_c_talap1_End;
	var1->mode = 0;
	var1->value.l = 0;
	var1->wtimer = 0;
}

// FUNCTION: SADX 0x008482c0
void ObjectSkydeck_c_talap1(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_talap1_Init(tp);
	}
}
