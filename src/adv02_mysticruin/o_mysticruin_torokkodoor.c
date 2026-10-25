#include "decls.h"
extern struct obj *DAT_060eea9c;

// FUNCTION: SADX 0x006b7b80
void ReserveColli(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct forcewk *var2 = tp->fwp;
	struct obj *var3;
	struct obj *var4;

	var2->pos_spd.x = 0.0f;
	var2->pos_spd.y = 0.0f;
	var2->pos_spd.z = 0.0f;
	((int *)var2)[1] = 0;
	((int *)var2)[2] = 0;
	((int *)var2)[3] = 0;
	var4 = *(struct obj **)((char *)DAT_060eea9c + 0x40);
	var3 = GetMobileLandObject();
	var1->value.ptr = var3;
	var3->evalflags = var4->evalflags;
	var3->scl[0] = 1.0f;
	var3->scl[1] = 1.0f;
	var3->scl[2] = 1.0f;
	var3->ang[0] = 0;
	var3->ang[1] = var1->ang.y;
	var3->ang[2] = 0;
	var3->pos[0] = var4->pos[0] + var1->pos.x;
	var3->pos[1] = var4->pos[1] + var1->pos.y;
	var3->pos[2] = var4->pos[2] + var1->pos.z;
	var3->model = var4->model;
	var3->child = 0;
	var3->sibling = 0;
	RegisterCollisionEntry(0x40000000, tp, var3);
}
