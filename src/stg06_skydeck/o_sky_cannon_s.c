#include "decls.h"
extern struct CCL_INFO object_cannon_s_info[1];
extern struct obj object_sky_st_houdai_st_houdai[1];
void ObjectSkydeck_cannon_s_Draw(struct task *tp);
void ObjectSkydeck_cannon_s_Exec(struct task *tp);
void FUN_00825de0(struct task *param_1);

// FUNCTION: SADX 0x0084a760
void ObjectSkydeck_cannon_s_Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_cannon_s_info, 1, 4);
		var1->cwp->colli_range = 100.0f;
		struct obj *var2 = GetMobileLandObject();
		var1->counter.ptr = var2;
		var2->scl[0] = 1.0f;
		var2->evalflags = 0;
		var2->scl[1] = 1.0f;
		var2->ang[0] = 0;
		var2->scl[2] = 1.0f;
		var2->ang[1] = *(long *)((char *)var1 + 0x18);
		var2->ang[2] = 0;
		var2->pos[0] = var1->pos.x;
		var2->pos[1] = var1->pos.y;
		var2->pos[2] = var1->pos.z;
		var2->model = object_sky_st_houdai_st_houdai[0].child->model;
		var2->child = object_sky_st_houdai_st_houdai[0].child->child;
		var2->sibling = 0;
		var1->flag |= 0x100;
		RegisterCollisionEntry(0x40000001, tp, var2);
	}
	tp->disp = ObjectSkydeck_cannon_s_Draw;
	tp->exec = ObjectSkydeck_cannon_s_Exec;
	tp->dest = FUN_00825de0;
	var1->mode = 0;
	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->btimer = 0;
	var1->wtimer = 0;
}

// FUNCTION: SADX 0x0084a830
void ObjectSkydeck_cannon_s(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		ObjectSkydeck_cannon_s_Init(tp);
	}
}
