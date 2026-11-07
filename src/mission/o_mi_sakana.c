#include "decls.h"

// GLOBAL: SADX 0x025a2b08
static struct NJS_POINT3 sakana_offset_tbl;

extern struct NJS_TEXLIST texlist_mi_meka_sakana;
int dsCheckView(float x, float y, float z, float radius);
extern int DAT_05cd2968;

// STUB: SADX 0x0049b3e0
void FUN_0049b3e0(struct NJS_MODEL *param_1)
{
}

// STUB: SADX 0x0049b910
void FUN_0049b910(struct task *param_1)
{
}

// STUB: SADX 0x0049b990
void FUN_0049b990(struct obj *param_1)
{
}

// FUNCTION: SADX 0x0049b9f0
void sakana_disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckView(var1->pos.x, var1->pos.y, var1->pos.z, 5.0f) == 0)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	FUN_0067d2d0(0, var1->scl.x, var1->scl.x, var1->scl.x);
	if (var1->ang.y + 0x8000 != 0)
	{
		njRotateY(0, (unsigned short)(0x8000 + (short)var1->ang.y));
	}
	if (var1->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)(short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(0, (unsigned short)(short)var1->ang.x);
	}
	njTranslateV(0, &sakana_offset_tbl);
	___njSetTexture(&texlist_mi_meka_sakana);
	FUN_004a88c0((NJS_ACTION *)var1->counter.ptr, var1->timer.f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0049baf0
void sakana_exit(struct task *tp)
{
	if (tp->awp)
	{
		struct task *var1 = (struct task *)tp->awp->work.ptr[2];
		if (var1 && var1->twp)
		{
			var1->twp->value.l = 0;
		}
		DAT_05cd2968--;
	}
}

// FUNCTION: SADX 0x0049bb20
void sakanaGeneraterExit(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (var1->value.ptr != 0)
	{
		DestroyTask((struct task *)var1->value.ptr);
		return;
	}
}

// STUB: SADX 0x0049c020
void sakanaInitialize(struct task *tp)
{
}

// STUB: SADX 0x0049c0a0
struct task *setSakana(struct task *tp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x0049c270
void ObjectMiSakana(struct task *tp)
{
	if (IsMissionAppear(tp))
	{
		MiSakanaGenerater(tp);
	}
}
