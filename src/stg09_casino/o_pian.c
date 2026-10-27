#include "decls.h"
extern struct NJS_ACTION action_pian_sleep_karada[];
extern struct NJS_ACTION action_pian_walk_karada[];
extern void FUN_007d21b0(...);
extern struct NJS_ACTION action_pian_pach_karada[];
void FUN_007d21b0(...);
static void Normal(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x00880140
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(0, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	FUN_004a88c0((NJS_ACTION *)var1->counter.ptr, *(float *)((char *)var1 + 0x10));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008803b0
static void Normal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
	{
		var1->value.f += 0.1f;
		if (var1->value.f >= 15.0f)
		{
			var1->value.f = 0.0f;
		}
		Disp(tp);
	}
}

// FUNCTION: SADX 0x00880470
void ObjectPianPach(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
	{
		var1->counter.ptr = &action_pian_pach_karada;
		var1->value.f = 0.0f;
		tp->exec = Normal;
		tp->disp = Disp;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}

// FUNCTION: SADX 0x008804c0
void ObjectPianWalk(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
	{
		var1->counter.ptr = &action_pian_walk_karada;
		var1->value.f = 0.0f;
		tp->exec = Normal;
		tp->disp = Disp;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}

// FUNCTION: SADX 0x00880510
void ObjectPianFish(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
	{
		var1->counter.ptr = &action_pian_fishing_karada;
		var1->value.f = 0.0f;
		tp->exec = Normal;
		tp->disp = Disp;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}

// FUNCTION: SADX 0x00880560
void ObjectPianSlee(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
	{
		var1->counter.ptr = &action_pian_sleep_karada;
		var1->value.f = 0.0f;
		tp->exec = Normal;
		tp->disp = Disp;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}
