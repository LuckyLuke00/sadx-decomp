#include "decls.h"
void FUN_00689420(struct task *param_1);
void FUN_006898a0(struct task *param_1);
void Exec(struct task *tp);
static void Exec(struct task *tp);
void FUN_00689420(struct task *param_1);
long SeqCheckTenbou();
void BoxInit(struct task *tp);

// STUB: SADX 0x00689320
long SeqCheckHighway()
{
	return (long)0;
}

// STUB: SADX 0x006893b0
long SeqCheckTenbou()
{
	return (long)0;
}

// STUB: SADX 0x00689580
void ColliSet(struct taskwk *twp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x006895f0
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006898a0
void FUN_006898a0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckRangeOut(param_1) == 0)
	{
		if (FUN_004c39c0(param_1) == 0)
		{
			if (var1->timer.ptr != 0)
			{
				if (((int (*)(void))var1->timer.ptr)() != 0)
				{
					var1->mode = 0;
					param_1->exec = Exec;
				}
			}
			EntryColliList(var1);
			LoopTaskC(param_1);
		}
		FUN_00689420(param_1);
	}
}

// FUNCTION: SADX 0x00689900
void BoxInit(struct task *tp)
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
	var3 = GetMobileLandObject();
	var1->counter.ptr = var3;
	var3->scl[0] = 1.0f;
	var3->scl[1] = 1.0f;
	var3->scl[2] = 1.0f;
	var3->evalflags = 0x34;
	var3->ang[0] = 0;
	var3->ang[1] = var1->ang.y;
	var3->ang[2] = 0;
	var3->pos[0] = var1->pos.x;
	var3->pos[1] = var1->pos.y;
	var3->pos[2] = var1->pos.z;
	var3->model = ((struct obj *)tp->ptp->twp->counter.ptr)->model;
	var3->child = 0;
	var3->sibling = 0;
	RegisterCollisionEntry(0x60000001, tp, var3);
	var1->flag |= 0x100;
	tp->exec = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->dest = FUN_00825de0;
}

// STUB: SADX 0x006899a0
void ObjectSSTenbouele(struct task *tp)
{
}

// STUB: SADX 0x00689a90
void ObjectSSHotelele(struct task *tp)
{
}

// STUB: SADX 0x00689b00
void ObjectSSHighwayele(struct task *tp)
{
}
