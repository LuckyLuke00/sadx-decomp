#include "decls.h"

// FUNCTION: SADX 0x00873e60
void ObjectCasinoRectangle2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->exec = ExecRectangle2;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, object_c_info_rectangle2, 1, 4);
			var1->cwp->info->a = var1->scl.x;
			var1->cwp->info->b = var1->scl.y;
			var1->cwp->info->c = var1->scl.z;
			CalcColliRange(var1->cwp);
		}
	}
}

// FUNCTION: SADX 0x00873ee0
void ObjectCasinoCylinder2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->exec = ExecCylinder2;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, object_c_info_cylinder2, 1, 4);
			var1->cwp->info->a = var1->scl.x;
			var1->cwp->info->b = var1->scl.y;
			var1->cwp->info->c = var1->scl.z;
			CalcColliRange(var1->cwp);
		}
	}
}

// FUNCTION: SADX 0x00873f60
void ObjectCasinoCapsule(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->exec = ExecCapsule;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, object_c_info_capsule, 1, 4);
			var1->cwp->info->a = var1->scl.x;
			var1->cwp->info->b = var1->scl.y;
			var1->cwp->info->c = var1->scl.z;
			CalcColliRange(var1->cwp);
		}
	}
}
