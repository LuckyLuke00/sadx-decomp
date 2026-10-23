#include "decls.h"
extern "C" double fabs(double param_1);

// FUNCTION: SADX 0x0087e030
void ObjectCasinoDmgSphereExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		if (FUN_004c39c0(tp) != 0)
		{
			njPrintC(0x120013, "-> SphereScale");
			ObjCasino_DrawSphere(&var1->pos, var1->scl.x);
			return;
		}
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x0087e090
void ObjectCasinoDmgSphere(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_c_info_sphere[0], 1, 4);
			var1->cwp->info->a = fabs(var1->scl.x);
			CalcColliRange(var1->cwp);
		}
		tp->exec = ObjectCasinoDmgSphereExec;
	}
}
