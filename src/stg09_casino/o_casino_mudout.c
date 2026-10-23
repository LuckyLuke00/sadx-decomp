#include "decls.h"
void njPrintC(int param_1, char const *param_2);
extern int DAT_060dc264;
extern float DAT_060dc260;

// FUNCTION: SADX 0x0086e2f0
float ObjectCasinoGetMud()
{
	return DAT_060dc260;
}

// STUB: SADX 0x0086e300
void ObjectCasinoSetMud(float mud)
{
}

// FUNCTION: SADX 0x0086e360
int FUN_0086e360(struct task *param_1)
{
	return FUN_004c39c0(param_1);
}

// FUNCTION: SADX 0x0086e370
void ExecMud(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) != 0)
	{
		njPrintC(0x140013, "Only 1 Obj!");
		return;
	}
	if (DAT_060dc264 != 0)
	{
		var1->wtimer++;
		if (var1->wtimer > 5)
		{
			DAT_060dc264 = 0;
			var1->wtimer = 0;
		}
	}
}

// FUNCTION: SADX 0x0086e520
void ObjectCasinoMud(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	tp->dest = (void (__cdecl *)(struct task *))FUN_0086e360;
	tp->exec = ExecMud;
	if (FUN_004c39c0(tp))
	{
		var1->value.l = 0;
		var1->timer.l = 0;
		return;
	}
	var1->wtimer = 0xffff;
}

// FUNCTION: SADX 0x0086e560
void ObjectCasinoMudout(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		tp->exec = ExecMudout;
		var1->wtimer = 0;
		var1->counter.l = 0;
	}
}
