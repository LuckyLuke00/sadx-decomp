#include "decls.h"

// FUNCTION: SADX 0x0082a6b0
void FUN_0082a6b0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct OBJ_CONDITION *var2 = (struct OBJ_CONDITION *)var1->counter.ptr;
	if (var2 != 0)
	{
		float var3;
		*(float *)((char *)var2 + 8) = var1->pos.x;
		*(float *)((char *)var2 + 0xc) = var1->pos.y;
		*(float *)((char *)var2 + 0x10) = var1->pos.z;
		*(long *)((char *)var2 + 0x14) = var1->ang.x;
		*(long *)((char *)var2 + 0x18) = var1->ang.y;
		*(long *)((char *)var2 + 0x1c) = var1->ang.z;
		var3 = var1->scl.y;
		if (CheckCollisionP(&var1->pos, *(float *)((char *)var2->pTask + 0x24) * var3 + 20.0f))
		{
			var1->flag |= 0x100;
			return;
		}
		var1->flag &= 0xfeff;
	}
}

// FUNCTION: SADX 0x0082a800
void GCInit_BPole(struct task *tp)
{
	struct obj *var1;
	struct taskwk *var2;

	var2 = tp->twp;
	var1 = GetMobileLandObject();
	var2->counter.ptr = var1;
	var1->scl[0] = 1.0f;
	var1->scl[1] = 1.0f;
	var1->evalflags = 0x10;
	var1->scl[2] = 1.0f;
	var1->ang[0] = var2->ang.x;
	var1->ang[1] = var2->ang.y;
	var1->ang[2] = var2->ang.z;
	var1->pos[0] = var2->pos.x;
	var1->pos[1] = var2->pos.y;
	var1->pos[2] = var2->pos.z;
	var1->model = *(struct NJS_MODEL **)((char *)var2->timer.ptr + 4);
	var1->child = *(struct obj **)((char *)var2->timer.ptr + 0x2c);
	var1->sibling = *(struct obj **)((char *)var2->timer.ptr + 0x30);
	RegisterCollisionEntry(1, tp, var1);
}

// FUNCTION: SADX 0x0082a870
void GC_BPole(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct OBJ_CONDITION *var2 = (struct OBJ_CONDITION *)var1->counter.ptr;
	if (var2 != 0)
	{
		*(float *)((char *)var2 + 8) = var1->pos.x;
		*(float *)((char *)var2 + 0xc) = var1->pos.y;
		*(float *)((char *)var2 + 0x10) = var1->pos.z;
		*(long *)((char *)var2 + 0x14) = var1->ang.x;
		*(long *)((char *)var2 + 0x18) = var1->ang.y;
		*(long *)((char *)var2 + 0x1c) = var1->ang.z;
		if (CheckCollisionP(&var1->pos, *(float *)((char *)var2->pTask + 0x24) + 20.0f))
		{
			var1->flag |= 0x100;
			return;
		}
		var1->flag &= 0xfeff;
	}
}

// FUNCTION: SADX 0x0082a8f0
void Object_Mountain_Zako(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp))
		{
			Object_Mountain_Zako_Display(tp);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			Object_Mountain_Zako_Display(tp);
			GCInit_Zako(tp);
			tp->disp = Object_Mountain_Zako_Display;
			tp->dest = FUN_00825de0;
			var1->mode = 1;
			break;
		case 1:
			Object_Mountain_Zako_Display(tp);
			GC_Zako(tp);
			return;
		}
	}
}

// FUNCTION: SADX 0x0082ac70
void Object_Mountain_BPole(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp))
		{
			Object_Mountain_BPole_Display(tp);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			Object_Mountain_BPole_Display(tp);
			GCInit_BPole(tp);
			tp->disp = Object_Mountain_BPole_Display;
			tp->dest = FUN_00825de0;
			var1->mode = 1;
			break;
		case 1:
			Object_Mountain_BPole_Display(tp);
			GC_BPole(tp);
			return;
		}
	}
}
