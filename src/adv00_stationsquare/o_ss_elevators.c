#include "decls.h"
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
