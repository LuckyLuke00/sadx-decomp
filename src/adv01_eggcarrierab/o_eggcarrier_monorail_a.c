#include "decls.h"

// FUNCTION: SADX 0x00698b20
void MonorailCarDestructor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	FreeTaskC(tp);
}

// FUNCTION: SADX 0x00698ce0
void StepsLand(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = tp->ptp->twp;
	switch (var1->mode)
	{
		case 0:
		{
			struct obj *var3 = GetMobileLandObject();
			var1->counter.ptr = var3;
			var3->scl[0] = 1.0f;
			var3->scl[1] = 1.0f;
			var3->evalflags = 0x10;
			var3->scl[2] = 1.0f;
			var3->ang[0] = 0;
			var3->ang[1] = var1->ang.y;
			var3->ang[2] = 0;
			var3->pos[0] = var1->pos.x;
			var3->pos[1] = var1->pos.y;
			var3->pos[2] = var1->pos.z;
			var3->model = (struct NJS_MODEL *)*(int **)((char *)var1->timer.ptr + 4);
			var3->child = 0;
			var3->sibling = 0;
			RegisterCollisionEntry(0x40000001, tp, var3);
			var1->flag &= 0xfeff;
			tp->dest = FUN_00825de0;
			var1->mode = 1;
		}
		break;
		case 1:
		{
			var1->flag &= 0xfeff;
			if ((var2->flag & 0x100) && (var2->flag & 0x200))
			{
				struct obj *var4 = (struct obj *)var1->counter.ptr;
				var4->pos[0] = var2->pos.x;
				var4->pos[1] = var2->pos.y;
				var4->pos[2] = var2->pos.z;
				var4->ang[0] = var2->ang.x;
				var4->ang[1] = var2->ang.y;
				var4->ang[2] = var2->ang.z;
				var1->flag |= 0x100;
			}
		}
		break;
	}
}
