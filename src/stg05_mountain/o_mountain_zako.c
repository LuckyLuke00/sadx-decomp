#include "decls.h"

// STUB: SADX 0x0082a6b0
void FUN_0082a6b0(struct task *tp)
{
}

// STUB: SADX 0x0082a800
void GCInit_BPole(struct task *tp)
{
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
