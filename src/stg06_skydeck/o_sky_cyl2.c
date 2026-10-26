#include "decls.h"
extern int DAT_05cbef64;

// FUNCTION: SADX 0x00847040
void ObjectSkydeck_c_cyl2_Exec(struct task *tp)
{
	if (SDCheckRangeOut(tp) == 0 && (DAT_05cbef64 & 1) != 0)
	{
		ObjectSkydeck_c_cyl2_Draw(tp);
		LoopTaskC(tp);
		FUN_004c39c0(tp);
	}
}

// FUNCTION: SADX 0x00847080
void ObjectSkydeck_c_cyl2_Init(struct task *tp)
{
	struct taskwk *local_10 = tp->twp;
	struct obj *local_c;
	struct task *local_8;
	if (FUN_004c39c0(tp) == 0)
	{
		local_c = GetMobileLandObject();
		local_10->counter.ptr = local_c;
		local_c->scl[0] = 1.0f;
		local_c->scl[1] = 1.0f;
		local_c->evalflags = 0;
		local_c->scl[2] = 1.0f;
		local_c->ang[0] = 0;
		local_c->ang[1] = local_10->ang.y;
		local_c->ang[2] = 0;
		local_c->pos[0] = local_10->pos.x;
		local_c->pos[1] = local_10->pos.y;
		local_c->pos[2] = local_10->pos.z;
		local_c->model = object_sky_obj_maru2asi_obj_maru2asi[0].model;
		local_c->child = object_sky_obj_maru2asi_obj_maru2asi[0].child;
		local_c->sibling = 0;
		local_10->flag |= 0x100;
		RegisterCollisionEntry(0x20000001, tp, local_c);
	}
	tp->disp = ObjectSkydeck_c_cyl2_Draw;
	tp->exec = ObjectSkydeck_c_cyl2_Exec;
	tp->dest = ObjectSkydeck_c_cyl1_End;
	local_10->wtimer = 0;
	local_10->mode = 0;
	local_10->value.l = 0;
	local_8 = CreateChildTask(3, ObjectSkydeck_c_cyl0_Grab, tp);
	local_8->twp->pos.x = local_10->pos.x;
	local_8->twp->pos.y = local_10->pos.y;
	local_8->twp->pos.z = local_10->pos.z;
}

// FUNCTION: SADX 0x00847150
void ObjectSkydeck_c_cyl2(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_cyl2_Init(tp);
	}
}
