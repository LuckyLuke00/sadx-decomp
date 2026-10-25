#include "decls.h"
static void DispH(struct task *tp);
static void ExecC(struct task *tp);
void FUN_008895d0(struct task *param_1);
extern void *DAT_060dc258;

// FUNCTION: SADX 0x0086bb40
void ObjectCasinoCrashSoniczoEnd(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	FUN_008895d0(tp);
	Free(*(void **)((char *)var1->value.ptr + 4));
	Free(var1->value.ptr);
	if (DAT_060dc258 == var1)
	{
		DAT_060dc258 = 0;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0086bd20
static void DispH(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0086be30
void ExecH(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		DispH(tp);
		if (FUN_004c39c0(tp) != 0)
		{
			njPrintC(0x120013, "-> Scale");
		}
	}
}

// FUNCTION: SADX 0x0086bfc0
static void ExecC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		if (FUN_004c39c0(tp) != 0)
		{
			njPrintC(0x120013, "-> Scale");
			ObjCasino_DrawSphere(&var1->pos, var1->scl.x);
			return;
		}
		if (DAT_060dc258 != 0 && *(char *)DAT_060dc258 == 2)
		{
			EntryColliList(var1);
		}
	}
}

// FUNCTION: SADX 0x0086c030
void ObjectCasinoSoniczoCollSphere(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 62510.0f))
		return;
	tp->exec = ExecC;
	if (FUN_004c39c0(tp))
		return;
	CCL_Init(tp, object_c_sphere, 1, 4);
	var1->cwp->info->a = var1->scl.x;
	var1->cwp->info->b = var1->scl.y;
	var1->cwp->info->c = var1->scl.z;
	CalcColliRange(var1->cwp);
}
