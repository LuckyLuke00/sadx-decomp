#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern struct obj object_enecrg_cl_enecrg_cl_enecrg[1];

// FUNCTION: SADX 0x008a3ea0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_HotShelter4);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	___dsAction(action_enecrg_enemycont, var1->timer.f, 1.0f);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x008a3f20
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008a40d0
void ObjShelterEnemycontainer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2;

	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->mode = 0;
	var1->wtimer = 0x12c;
	if (FUN_004c39c0(tp) == 0)
	{
		var2 = GetMobileLandObject();
		var1->counter.ptr = var2;
		var2->scl[0] = 1.0f;
		var2->scl[1] = 1.0f;
		var2->scl[2] = 1.0f;
		var2->evalflags = 0x10;
		var2->ang[0] = 0;
		var2->ang[1] = var1->ang.y;
		var2->ang[2] = 0;
		var2->pos[0] = var1->pos.x;
		var2->pos[1] = var1->pos.y;
		var2->pos[2] = var1->pos.z;
		var2->model = object_enecrg_cl_enecrg_cl_enecrg[0].model;
		var2->child = 0;
		var2->sibling = 0;
		RegisterCollisionEntry(0x28000000, tp, var2);
		var1->flag |= 0x100;
		CreateChildTask(6, DoorInit, tp);
	}
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = MonorailCarDestructor;
}
