#include "decls.h"
extern struct obj object_b_con_cl_conbere_cl_side[];
void SideTaskExec(struct task *tp);

// FUNCTION: SADX 0x0089ddc0
void SideTaskExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckCollisionP(&var1->pos, tp->ptp->twp->scl.z * 128.0f + 20.0f) == 1)
	{
		var1->flag |= 0x100;
		return;
	}
	var1->flag &= 0xfeff;
}

// FUNCTION: SADX 0x0089de40
void SideTask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct forcewk *var2 = tp->fwp;
	struct obj *var3;
	float *var4;

	var4 = (float *)var2;
	var4[4] = 0.0f;
	var4[5] = 0.0f;
	var4[6] = 0.0f;
	((int *)var2)[1] = 0;
	((int *)var2)[2] = 0;
	((int *)var2)[3] = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		var3 = GetMobileLandObject();
		var1->counter.ptr = var3;
		var3->evalflags = object_b_con_cl_conbere_cl_side[0].evalflags;
		var3->scl[0] = 1.0f;
		var3->scl[1] = 1.0f;
		var3->scl[2] = tp->ptp->twp->scl.z;
		var3->ang[0] = 0;
		var3->ang[1] = var1->ang.y;
		var3->ang[2] = 0;
		var3->pos[0] = var1->pos.x;
		var3->pos[1] = var1->pos.y;
		var3->pos[2] = var1->pos.z;
		var3->model = object_b_con_cl_conbere_cl_side[0].model;
		var3->child = 0;
		var3->sibling = 0;
		RegisterCollisionEntry(0, tp, var3);
	}
	tp->disp = 0;
	tp->exec = SideTaskExec;
	tp->dest = KasyaDestruct;
}
